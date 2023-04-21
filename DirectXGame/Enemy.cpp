#include "Enemy.h"
#include "MathUtils.h"
#include <cassert>

void Enemy::Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity) {
	assert(model);
	m_model = model;
	m_texutreHandle = texHandle;
	m_worldTransform.Initialize();
	m_velocity = velocity;
	m_worldTransform.translation_ = {0.0f,1.0f,10.0f};
}

void Enemy::Update() { 
	m_worldTransform.translation_ += m_velocity;
	m_worldTransform.UpdateMatrix(); 
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_texutreHandle);
}
