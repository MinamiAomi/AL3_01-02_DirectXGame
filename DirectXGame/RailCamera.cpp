#include "RailCamera.h"
#include "ImGuiManager.h"
#include "MathUtils.h"
#include <vector>
#include "PrimitiveDrawer.h"

void RailCamera::Initalize(const Vector3& pos, const Vector3& rot) {

	m_worldTransform.scale_ = {1.0f, 1.0f, 1.0f};
	m_worldTransform.translation_ = pos;
	m_worldTransform.rotation_ = rot;

	m_viewProjection.Initialize();

	std::vector<Vector3> controlPoints = {
	    {0.0f,  0.0f,  -50.0f },
	    {-50.0f, 0.0f,  10.0f},
	    {0.0f,  -5.0f, 50.0f},
	    {50.0f,  5.0f,  10.0f},
	    {30.0f,  10.0f,  0.0f},
	    {10.0f,  -5.0f,  10.0f},
	};

	m_rail.AddControlPoints(controlPoints);
	m_rail.SetIsLoop(true);

	m_moveTime = 0;
}

void RailCamera::Update() {

	if (++m_moveTime >= kLoopTime) {
		m_moveTime = 0;
	}

	size_t sectionCount = m_rail.GetSectionCount();
	uint32_t sectionTime = kLoopTime / static_cast<uint32_t>(sectionCount);
	auto ReilPoint = [=](uint32_t moveTime) {
		uint32_t section = moveTime / sectionTime;
		float t = static_cast<float>(moveTime % sectionTime) / static_cast<float>(sectionTime);
		return m_rail.ComputePoint(t, section);
	};

	Vector3 eye = ReilPoint(m_moveTime);
	Vector3 target = ReilPoint((m_moveTime + 5) % kLoopTime);
	
	m_worldTransform.translation_ = eye;

	Vector3 toTarget = target - eye;
	m_worldTransform.rotation_.y = std::atan2(toTarget.x, toTarget.z);
	float velXZLen = Length(Vector2(toTarget.x, toTarget.z));
	m_worldTransform.rotation_.x = std::atan2(-toTarget.y, velXZLen);

	m_worldTransform.matWorld_ = MakeAffineMatrix(
	    m_worldTransform.scale_, m_worldTransform.rotation_, m_worldTransform.translation_);
	m_viewProjection.matView = Inverse(m_worldTransform.matWorld_);

	m_viewProjection.TransferMatrix();

	ImGui::SetNextWindowPos({0, 200}, ImGuiCond_Once);
	ImGui::SetNextWindowSize({300, 200}, ImGuiCond_Once);
	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("Position", &m_worldTransform.translation_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &m_worldTransform.rotation_.x, 0.01f, 0.0f, Math::TwoPi);
	int a = (int)m_moveTime;	
	ImGui::SliderInt("MoveTime", &a, 0, (int)kLoopTime);
	m_moveTime = (uint32_t)a;
	ImGui::End();
}

void RailCamera::Draw() {
	size_t pointCount = 100;
	std::vector<Vector3> pointDrawing(pointCount);
	size_t sectionCount = m_rail.GetSectionCount();
	float t = 0.0f;
	size_t section = 0;
	float deltaT = (float)sectionCount / (float)pointCount;
	for (size_t i = 0; i < pointDrawing.size(); ++i) {
		pointDrawing[i] = m_rail.ComputePoint(t, section);
		t += deltaT;
		if (1.0f < t) {
			t -= 1.0f;
			++section;
		}
	}

	for (uint32_t i = 0; i < pointCount; ++i) {
		uint32_t j = (i + 1) % pointCount;
		PrimitiveDrawer::GetInstance()->DrawLine3d(
		    pointDrawing[i], pointDrawing[j], {1.0f, 0.0f, 0.0f, 1.0f});
	}
}
