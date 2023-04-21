#pragma once
#include "EnemyBullet.h"
#include "EnemyStates.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cstdint>
#include <memory>

class Player;

class Enemy {
public:
	void Initalize(
	    const std::shared_ptr<Player>& player, const std::shared_ptr<Model>& model,
	    const std::shared_ptr<Model>& bulletModel, uint32_t texHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	inline void SetTranslation(const Vector3& translation) {
		m_worldTransform.translation_ = translation;
	}
	inline const Vector3& GetTranslation() const { return m_worldTransform.translation_; }
	inline const Vector3& GetVelocity() const { return m_velocity; }

	void ChangeState(std::unique_ptr<EnemyState> state);
	void FireBullet();

private:
	std::shared_ptr<Player> m_player;

	WorldTransform m_worldTransform;
	Vector3 m_velocity{};

	std::unique_ptr<EnemyState> m_state;

	std::shared_ptr<Model> m_model;
	std::shared_ptr<Model> m_bulletModel;
	uint32_t m_texutreHandle = 0u;

	std::list<std::unique_ptr<EnemyBullet>> m_bullets;
};
