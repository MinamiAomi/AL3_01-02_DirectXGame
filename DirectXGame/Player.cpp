#include "Player.h"
#include <cassert>
#include "Input.h"
#include "MathUtils.h"
#include "ImGuiManager.h"

static float imguiPos[3] = {};

void Player::Initalize(std::shared_ptr<Model> model, uint32_t texHandle) { 
	assert(model);	

	m_model = model;
	m_textureHandle = texHandle;
	m_worldTransform.Initialize();
}

void Player::Update() { 
	auto input = Input::GetInstance();
	
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	if (input->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} 
	if (input->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} 
	if (input->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	m_worldTransform.translation_+= move;


	m_worldTransform.matWorld_ = MakeAffineMatrix(
	    m_worldTransform.scale_, m_worldTransform.rotation_, m_worldTransform.translation_);

	m_worldTransform.TransferMatrix();

	Copy(m_worldTransform.translation_, imguiPos);

	ImGui::Begin("Player");
	ImGui::SetWindowPos({0, 0});
	ImGui::SetWindowSize({300, 100});
	ImGui::InputFloat3("Position", imguiPos);
	ImGui::End();
}

void Player::Draw(const ViewProjection& viewProjection) {

	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}
