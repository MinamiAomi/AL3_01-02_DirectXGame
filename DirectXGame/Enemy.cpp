#include "Enemy.h"
#include <cassert>
#include "Player.h"
#include "ImGuiManager.h"
#include "CollisionCofig.h"


void Enemy::Initalize(const Vector3& position) {
	
	m_worldTransform.Initialize();
	m_velocity = {0.0f, 0.0f, -0.2f};
	m_worldTransform.translation_ = position;
	m_worldTransform.rotation_ = {0.0f, Math::ToRad(180.0f), 0.0f};
	m_worldTransform.UpdateMatrix();
	ChangeState(std::make_unique<EnemyStateApproach>());

	SetRadius(1.0f);
	SetCollisionAttribute(CollisionConfig::kAttributeEnemy);
	SetCollisionMask(~CollisionConfig::kAttributeEnemy);
}

void Enemy::Update() {

	m_state->Update();

	m_worldTransform.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}
 
void Enemy::OnCollision() { m_isDead = true; }

void Enemy::ChangeState(std::unique_ptr<EnemyState> state) {
	m_state = std::move(state);
	m_state->Initalize(this);
}

void Enemy::FireBullet() {
	const float kBulletSpeed = 1.0f;

	Vector3 playerPosition = m_player->GetWorldPosition();
	Vector3 enemyPosition = GetTranslate(m_worldTransform.matWorld_);
	Vector3 velocity = playerPosition - enemyPosition;
	velocity = Normalize(velocity) * kBulletSpeed;

	auto& newBullet = m_enemyBulletManager->AddBullet();
	newBullet.Initalize(m_worldTransform.translation_, velocity);
}
