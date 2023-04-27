#include "Player.h"
#include "ImGuiManager.h"
#include "Input.h"
#include <cassert>
#include "CollisionCofig.h"

void Player::Initalize(
    const std::shared_ptr<Model>& model, 
	const std::shared_ptr<Model>& bulletModel,
    uint32_t texHandle) {
	assert(model);
	assert(bulletModel);

	m_model = model;
	m_bulletModel = bulletModel;
	m_textureHandle = texHandle;
	m_worldTransform.Initialize();

	SetRadius(1.0f);
	SetCollisionAttribute(CollisionConfig::kAttributePlayer);
	SetCollisionMask(~CollisionConfig::kAttributePlayer);
}

void Player::Update() {

	// 弾を削除
	m_bullets.remove_if([](auto& bullet) { return bullet->IsDead(); });

	// 旋回処理
	Rotate();
	// 移動処理
	Move();
	m_worldTransform.UpdateMatrix();

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

void Player::Attack() {
	auto input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity{0.0f, 0.0f, kBulletSpeed};

		velocity = TransformNormal(velocity, m_worldTransform.matWorld_);

		auto newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initalize(m_bulletModel, m_worldTransform.translation_, velocity);

		m_bullets.push_back(std::move(newBullet));
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
	ImGui::InputFloat3("Position", imguiPos);
	ImGui::InputFloat3("Rotate", imguiRot);
	ImGui::End();
}
