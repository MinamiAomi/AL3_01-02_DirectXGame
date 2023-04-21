#include "Enemy.h"
#include "MathUtils.h"
#include <cassert>

void Enemy::Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity) {
	assert(model);
	m_model = model;
	m_texutreHandle = texHandle;
	m_worldTransform.Initialize();
	m_velocity = velocity;
	m_worldTransform.translation_ = {0.0f, 1.0f, 10.0f};
	m_worldTransform.rotation_ = {0.0f, Math::ToRad(180.0f), 0.0f};
	ChangeState(std::make_unique<EnemyStateApproach>(this));
}

void Enemy::Update() {
	
	m_state->Update();

	m_worldTransform.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_texutreHandle);
}

void Enemy::ChangeState(std::unique_ptr<EnemyState> state) { m_state = std::move(state); }
