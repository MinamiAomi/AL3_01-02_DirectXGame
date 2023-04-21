#include "Enemy.h"
#include "MathUtils.h"
#include <cassert>

void (Enemy::*Enemy::s_phaseFuncTable[])() = {
	&Enemy::ApproachPhase,
	&Enemy::LeavePhase
};

void Enemy::Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity) {
	assert(model);
	m_model = model;
	m_texutreHandle = texHandle;
	m_worldTransform.Initialize();
	m_velocity = velocity;
	m_worldTransform.translation_ = {0.0f, 1.0f, 10.0f};
	m_worldTransform.rotation_ = {0.0f, Math::ToRad(180.0f), 0.0f};
}

void Enemy::Update() {
	
	(this->*s_phaseFuncTable[static_cast<size_t>(m_phase)])();

	m_worldTransform.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_texutreHandle);
}

void Enemy::ApproachPhase() {
	m_worldTransform.translation_ += m_velocity;
	if (m_worldTransform.translation_.z < 0.0f) {
		m_phase = Phase::Leave;
	}
}

void Enemy::LeavePhase() { 
	m_worldTransform.translation_ += -m_velocity * 1.0f;
	if (m_worldTransform.translation_.z > 100.0f) {
		m_phase = Phase::Approach;
	}
}
