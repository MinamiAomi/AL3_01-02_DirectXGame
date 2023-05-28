#include "Player.h"
#include "CollisionCofig.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "TextureManager.h"
#include "WinApp.h"
#include <cassert>

void Player::Initalize(
    const std::shared_ptr<Model>& model, const std::shared_ptr<Model>& bulletModel,
    uint32_t texHandle) {
	assert(model);
	assert(bulletModel);

	m_model = model;
	m_bulletModel = bulletModel;
	m_textureHandle = texHandle;
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = {0.0f, 0.0f, 0.0f};

	uint32_t texture = TextureManager::Load("Reticle.png");
	m_sprite2DReticle.reset(Sprite::Create(texture, {}, {1.0f, 1.0f, 1.0f, 0.8f}, {0.5f, 0.5f}));

	SetRadius(1.0f);
	SetCollisionAttribute(CollisionConfig::kAttributePlayer);
	SetCollisionMask(~CollisionConfig::kAttributePlayer);
}

void Player::Update(const ViewProjection& viewProjection) {
	// 弾を削除
	m_bullets.remove_if([](auto& bullet) { return bullet->IsDead(); });

	// 旋回処理
	Rotate();
	// 移動処理
	Move();
	m_worldTransform.UpdateMatrix();

	ReticleUpdate(viewProjection);

	// 攻撃処理
	Attack();

	for (auto& bullet : m_bullets) {
		bullet->Update();
	}

	DebugUI();
}

void Player::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

	for (auto& bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}
}

void Player::DrawUI() { m_sprite2DReticle->Draw(); }

void Player::OnCollision() {}

void Player::Rotate() {
	constexpr float kRotateSpeed = Math::ToRad(1.0f);

	auto input = Input::GetInstance();

	if (input->PushKey(DIK_D)) {
		m_worldTransform.rotation_.y += kRotateSpeed;
	}
	if (input->PushKey(DIK_A)) {
		m_worldTransform.rotation_.y -= kRotateSpeed;
	}
}

void Player::Move() {
	// キャラクターの移動速度
	constexpr float kMoveSpeed = 0.2f;

	auto input = Input::GetInstance();

	if (input->PushKey(DIK_LEFT)) {
		m_worldTransform.translation_.x -= kMoveSpeed;
	}
	if (input->PushKey(DIK_RIGHT)) {
		m_worldTransform.translation_.x += kMoveSpeed;
	}

	if (input->PushKey(DIK_UP)) {
		m_worldTransform.translation_.y += kMoveSpeed;
	}
	if (input->PushKey(DIK_DOWN)) {
		m_worldTransform.translation_.y -= kMoveSpeed;
	}

	const float kMoveXLimit = 34.0f;
	const float kMoveYLimit = 18.0f;

	m_worldTransform.translation_.x =
	    std::clamp(m_worldTransform.translation_.x, -kMoveXLimit, kMoveXLimit);
	m_worldTransform.translation_.y =
	    std::clamp(m_worldTransform.translation_.y, -kMoveYLimit, kMoveYLimit);
}

void Player::ReticleUpdate(const ViewProjection& viewProjection) {
	
	// マウスのスクリーン座標を取得
	POINT mousePos{};
	GetCursorPos(&mousePos);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePos);
	Vector2 screenMousePos{static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)};
	m_sprite2DReticle->SetPosition(screenMousePos);

	// マウスをワールド座標に変換するための行列
	float width = static_cast<float>(WinApp::kWindowWidth);
	float height = static_cast<float>(WinApp::kWindowHeight);
	Matrix4x4 viewportMat = MakeViewportMatrix(0.0f, 0.0f, width, height, 0.0f, 1.0f);
	Matrix4x4 vpvMat = viewProjection.matView * viewProjection.matProjection * viewportMat;
	Matrix4x4 vpvMatInv = Inverse(vpvMat);
	// スクリーン座標系からワールド座標系に変換
	Vector3 mousePosNear{screenMousePos.x, screenMousePos.y, 0.0f};
	Vector3 mousePosFar{screenMousePos.x, screenMousePos.y, 1.0f};
	mousePosNear = Transform(mousePosNear, vpvMatInv);
	mousePosFar = Transform(mousePosFar, vpvMatInv);

	Vector3 mouseDirection = Normalize(mousePosFar - mousePosNear);
	m_reticlePosition =
	    mousePosNear + mouseDirection * (m_reticleDistance + m_worldTransform.translation_.z);
}

void Player::Attack() {
	auto input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 2.0f;
		Vector3 velocity = m_reticlePosition - GetTranslate(m_worldTransform.matWorld_);
		velocity = Normalize(velocity) * kBulletSpeed;

		Vector3 bulletInitPos = GetTranslate(m_worldTransform.matWorld_);
		auto newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initalize(m_bulletModel, bulletInitPos, velocity);

		m_bullets.emplace_back(std::move(newBullet));
	}
}

void Player::DebugUI() {
	static float imguiPos[3] = {};
	static float imguiRot[3] = {};
	Copy(m_worldTransform.translation_, imguiPos);
	Copy(m_worldTransform.rotation_, imguiRot);

	ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Once);
	ImGui::SetNextWindowSize({300, 100}, ImGuiCond_Once);
	ImGui::Begin("Player");
	ImGui::DragFloat3("Position", &m_worldTransform.translation_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &m_worldTransform.rotation_.x, 0.01f, 0.0f, Math::TwoPi);
	ImGui::DragFloat("ReticleDistance", &m_reticleDistance, 1.0f, 0.0f, 100.0f);
	ImGui::End();
}
