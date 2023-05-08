#pragma once
#include "Collider.h"
#include "EnemyBulletManager.h"
#include "EnemyStates.h"
#include "MathUtils.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cstdint>
#include <memory>

class Player;

class Enemy : public Collider {
public:
	void Initalize(const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision() override;

	inline const Vector3& GetTranslation() const { return m_worldTransform.translation_; }
	inline const Vector3& GetVelocity() const { return m_velocity; }
	inline Vector3 GetWorldPosition() const override {
		return GetTranslate(m_worldTransform.matWorld_);
	}

	inline void SetTranslation(const Vector3& translation) {
		m_worldTransform.translation_ = translation;
	}
	inline void SetPlayer(const std::shared_ptr<Player>& player) { m_player = player; }
	inline void SetBulletManager(const std::shared_ptr<EnemyBulletManager>& bulletManager) {
		m_enemyBulletManager = bulletManager;
	}
	inline void SetTextureHandle(uint32_t textureHandle) { m_textureHandle = textureHandle; }
	inline void SetModel(const std::shared_ptr<Model>& model) { m_model = model; }

	void ChangeState(std::unique_ptr<EnemyState> state);
	void FireBullet();

	inline bool IsDead() const { return m_isDead; }

private:
	std::shared_ptr<Player> m_player;
	std::shared_ptr<EnemyBulletManager> m_enemyBulletManager;
	
	WorldTransform m_worldTransform;
	Vector3 m_velocity{};

	std::unique_ptr<EnemyState> m_state;

	std::shared_ptr<Model> m_model;
	uint32_t m_textureHandle = 0u;

	bool m_isDead = false;
};
