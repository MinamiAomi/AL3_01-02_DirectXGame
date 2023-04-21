#pragma once
#include <cstdint>
#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class PlayerBullet {
public:
	static constexpr int32_t kLifeTime = 60 * 5;

	void Initalize(const std::shared_ptr<Model>& model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProj);

	inline bool IsDead() const { return m_isDead; }

private:
	WorldTransform m_worldTransform;
	Vector3 m_velocity{};
	int32_t m_deathTimer = kLifeTime;
	bool m_isDead = false;
	std::shared_ptr<Model> m_model;
	uint32_t m_textureHandle = 0u;
};
