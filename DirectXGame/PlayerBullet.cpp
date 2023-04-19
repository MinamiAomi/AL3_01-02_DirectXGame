#include "PlayerBullet.h"
#include <cassert>
#include "TextureManager.h"
#include "MathUtils.h"
#include "ImGuiManager.h"

void PlayerBullet::Initalize(std::shared_ptr<Model> model, const Vector3& position) {
	assert(model);

	m_model = model;
	m_textureHandle = TextureManager::GetInstance()->Load("black.png");
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
}

void PlayerBullet::Update() { 
	m_worldTransform.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProj) { 
	m_model->Draw(m_worldTransform, viewProj, m_textureHandle);
}

void PlayerBullet::DebugUI() {
	static float imguiPos[3] = {};
	Copy(m_worldTransform.translation_, imguiPos);

	ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Once);
	ImGui::SetNextWindowSize({300, 100}, ImGuiCond_Once);
	ImGui::Begin("Player");
	if (ImGui::TreeNode("Bullet")) {
		ImGui::InputFloat3("Position", imguiPos);
		ImGui::TreePop();
	}
	ImGui::End();
}
