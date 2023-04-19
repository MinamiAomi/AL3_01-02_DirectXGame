#include "Player.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MathUtils.h"
#include <cassert>

void Player::Initalize(std::shared_ptr<Model> model, uint32_t texHandle) {
	assert(model);

	m_model = model;
	m_textureHandle = texHandle;
	m_worldTransform.Initialize();
}

void Player::Update() {

	// 旋回処理
	Rotate();
	// 移動処理
	Move();
	// 攻撃処理
	Attack();

	if (m_bullet) {
		m_bullet->Update();
	}
	
	m_worldTransform.UpdateMatrix();

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

	if (m_bullet) {
		m_bullet->DebugUI();
	}
}

void Player::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);

	if (m_bullet) {
		m_bullet->Draw(viewProjection);
	}
}

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
		m_bullet = std::make_unique<PlayerBullet>();
		m_bullet->Initalize(m_model, m_worldTransform.translation_);
	}
}
