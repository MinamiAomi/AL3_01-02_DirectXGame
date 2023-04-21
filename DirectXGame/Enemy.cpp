#include "Enemy.h"
#include "MathUtils.h"
#include <cassert>

void Enemy::Initalize(
    std::shared_ptr<Model> model, 
	std::shared_ptr<Model> bulletModel, 
	uint32_t texHandle,
    const Vector3& velocity) {
	assert(model);
	assert(bulletModel);

	m_model = model;
	m_bulletModel = bulletModel;
	m_texutreHandle = texHandle;
	m_worldTransform.Initialize();
	m_velocity = velocity;
	m_worldTransform.translation_ = {5.0f, 2.0f, 50.0f};
	m_worldTransform.rotation_ = {0.0f, Math::ToRad(180.0f), 0.0f};
	ChangeState(std::make_unique<EnemyStateApproach>());
}

void Enemy::Update() {
	// 弾を削除
	m_bullets.remove_if([](auto& bullet) { return bullet->IsDead() ? true : false; });

	m_state->Update();

	m_worldTransform.UpdateMatrix();

	// 弾を更新
	for (auto& bullet : m_bullets) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_texutreHandle);

	for (auto& bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::ChangeState(std::unique_ptr<EnemyState> state) { 
	m_state = std::move(state);
	m_state->Initalize(this);
}

void Enemy::FireBullet() {
	const float kBulletSpeed = 1.0f;
	Vector3 velocity{0.0f, 0.0f, kBulletSpeed};

	velocity = TransformNormal(velocity, m_worldTransform.matWorld_);

	auto newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initalize(m_bulletModel, m_worldTransform.translation_, velocity);

	m_bullets.push_back(std::move(newBullet));
}
