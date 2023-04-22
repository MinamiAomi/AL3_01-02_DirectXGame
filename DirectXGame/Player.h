#pragma once
#include <cstdint>
#include <memory>
#include <list>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "PlayerBullet.h"
#include "MathUtils.h"


class Player {
public:
	void Initalize(const std::shared_ptr<Model>& model, const std::shared_ptr<Model>& bulletModel, uint32_t texHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	inline Vector3 GetWorldPosition() const { return GetTranslate(m_worldTransform.matWorld_); }
	inline const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return m_bullets; }

private:
	void Rotate();
	void Move();
	void Attack();
	void DebugUI();

	WorldTransform m_worldTransform;
	std::shared_ptr<Model> m_model;
	std::shared_ptr<Model> m_bulletModel;
	uint32_t m_textureHandle = 0u;

	std::list<std::unique_ptr<PlayerBullet>> m_bullets;
};
	  