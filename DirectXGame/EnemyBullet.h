#pragma once
#include "Collider.h"
#include "MathUtils.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cstdint>
#include <memory>

class Player;

class EnemyBullet : public Collider {
public:
	static constexpr int32_t kLifeTime = 60 * 5;

	static float slerpRatio;

	void Initalize(
	    const std::shared_ptr<Player>& player, const std::shared_ptr<Model>& model,
	    const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProj);

	void OnCollision() override;

	inline Vector3 GetWorldPosition() const override {
		return GetTranslate(m_worldTransform.matWorld_);
	}
	inline bool IsDead() const { return m_isDead; }

private:
	std::shared_ptr<Player> m_player;

	WorldTransform m_worldTransform;
	Vector3 m_velocity{};
	int32_t m_deathTimer = kLifeTime;
	bool m_isDead = false;
	std::shared_ptr<Model> m_model;
	uint32_t m_textureHandle = 0u;
};
