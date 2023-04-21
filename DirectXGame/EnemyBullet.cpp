#include "EnemyBullet.h"
#include <cassert>
#include "TextureManager.h"
#include "MathUtils.h"
#include "ImGuiManager.h"
#include "Player.h"

float EnemyBullet::slerpRatio = 0.1f;

void EnemyBullet::Initalize(
    const std::shared_ptr<Player>& player, 
    const std::shared_ptr<Model>& model, 
	const Vector3& position, 
	const Vector3& velocity) {
	assert(player);
	assert(model);

	m_player = player;
	m_velocity = velocity;
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
	m_worldTransform.scale_ = {1.0f, 1.0f, 1.5f};

	m_worldTransform.rotation_.y = std::atan2(m_velocity.x, m_velocity.z);
	float velXZLen = Length(Vector2(m_velocity.x, m_velocity.z));
	m_worldTransform.rotation_.x = std::atan2(-m_velocity.y,velXZLen);

	m_model = model;
	m_textureHandle = TextureManager::GetInstance()->Load("red.png");
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

