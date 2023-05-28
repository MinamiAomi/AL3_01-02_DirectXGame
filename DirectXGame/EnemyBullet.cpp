#include "EnemyBullet.h"
#include "CollisionCofig.h"
#include "Player.h"
#include <cassert>

float EnemyBullet::slerpRatio = 0.04f;

void EnemyBullet::Initalize(const Vector3& position, const Vector3& velocity) {

	m_velocity = velocity;
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
	m_worldTransform.scale_ = {1.0f, 1.0f, 1.5f};

	m_worldTransform.rotation_.y = std::atan2(m_velocity.x, m_velocity.z);
	float velXZLen = Length(Vector2(m_velocity.x, m_velocity.z));
	m_worldTransform.rotation_.x = std::atan2(-m_velocity.y, velXZLen);

	SetRadius(0.8f);
	SetCollisionAttribute(CollisionConfig::kAttributeEnemy);
	SetCollisionMask(~CollisionConfig::kAttributeEnemy);
}

void EnemyBullet::Update() {
	if (--m_deathTimer <= 0) {
		m_isDead = true;
	}

	Vector3 toPlayer = m_player->GetWorldPosition() - m_worldTransform.translation_;

	toPlayer = Normalize(toPlayer);
	m_velocity = Normalize(m_velocity);
	m_velocity = Slerp(slerpRatio, m_velocity, toPlayer);

	m_worldTransform.translation_ += m_velocity;

	m_worldTransform.rotation_.y = std::atan2(m_velocity.x, m_velocity.z);
	float velXZLen = Length(Vector2(m_velocity.x, m_velocity.z));
	m_worldTransform.rotation_.x = std::atan2(-m_velocity.y, velXZLen);

	m_worldTransform.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewProj) {
	m_model->Draw(m_worldTransform, viewProj, m_textureHandle);
}

void EnemyBullet::OnCollision() { m_isDead = true; }
