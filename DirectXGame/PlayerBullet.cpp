#include "PlayerBullet.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>

void PlayerBullet::Initalize(
    const std::shared_ptr<Model>& model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
	m_worldTransform.scale_ = {1.0f, 1.0f, 1.5f};
	m_velocity = velocity;

	m_worldTransform.rotation_.y = std::atan2(m_velocity.x, m_velocity.z);
	float velXZLen = Length(Vector2(m_velocity.x, m_velocity.z));
	m_worldTransform.rotation_.x = std::atan2(-m_velocity.y, velXZLen);
	m_worldTransform.UpdateMatrix();

	m_model = model;
	m_textureHandle = TextureManager::GetInstance()->Load("black.png");

	SetRadius(0.8f);
}

void PlayerBullet::Update() {
	if (--m_deathTimer <= 0) {
		m_isDead = true;
	}

	m_worldTransform.translation_ += m_velocity;

	m_worldTransform.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProj) {
	m_model->Draw(m_worldTransform, viewProj, m_textureHandle);
}

void PlayerBullet::OnCollision() { m_isDead = true; }

