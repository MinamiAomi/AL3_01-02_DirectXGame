#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cstdint>
#include <memory>
#include "EnemyStates.h"

class Enemy {
public:
	void Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	inline void SetTranslation(const Vector3& translation) { m_worldTransform.translation_ = translation; }
	inline const Vector3& GetTranslation() const { return m_worldTransform.translation_; }
	inline const Vector3& GetVelocity() const { return m_velocity; }

	void ChangeState(std::unique_ptr<EnemyState> state);

private:
	WorldTransform m_worldTransform;
	Vector3 m_velocity{};

	std::unique_ptr<EnemyState> m_state;

	std::shared_ptr<Model> m_model;
	uint32_t m_texutreHandle = 0u;
};
