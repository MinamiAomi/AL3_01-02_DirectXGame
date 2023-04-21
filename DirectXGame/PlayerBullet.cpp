#include "PlayerBullet.h"
#include <cassert>
#include "TextureManager.h"
#include "MathUtils.h"
#include "ImGuiManager.h"

void PlayerBullet::Initalize(const std::shared_ptr<Model>& model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	m_worldTransform.Initialize();
	m_worldTransform.translation_ = position;
	m_worldTransform.scale_ = {1.0f, 1.0f, 1.5f};
	m_velocity = velocity;

	m_model = model;
	m_textureHandle = TextureManager::GetInstance()->Load("black.png");
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

