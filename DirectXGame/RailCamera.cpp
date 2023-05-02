#include "RailCamera.h"
#include "MathUtils.h"
#include "ImGuiManager.h"

void RailCamera::Initalize(const Vector3& pos, const Vector3& rot) {
	
	m_worldTransform.scale_ = {1.0f, 1.0f, 1.0f};
	m_worldTransform.translation_ = pos;
	m_worldTransform.rotation_ = rot;

	m_viewProjection.Initialize();
}

void RailCamera::Update() { 
	
	
	m_worldTransform.matWorld_ = MakeAffineMatrix(
	    m_worldTransform.scale_, m_worldTransform.rotation_, m_worldTransform.translation_);
	m_viewProjection.matView = Inverse(m_worldTransform.matWorld_);

	m_viewProjection.TransferMatrix();

	ImGui::SetNextWindowPos({0, 200}, ImGuiCond_Once);
	ImGui::SetNextWindowSize({300, 200}, ImGuiCond_Once);
	ImGui::Begin("RailCamera");
	ImGui::InputFloat3("Position", &m_worldTransform.translation_.x);
	ImGui::SliderFloat3("Rotate", &m_worldTransform.rotation_.x, 0.0f, Math::TwoPi);
	ImGui::End();
}

void RailCamera::Draw() {}
