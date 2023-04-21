#pragma once
#include <cstdint>
#include <memory>
#include <list>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "PlayerBullet.h"


class Player {
public:
	void Initalize(std::shared_ptr<Model> model, uint32_t texHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	void Rotate();
	void Move();
	void Attack();
	void DebugUI();

	WorldTransform m_worldTransform;
	std::shared_ptr<Model> m_model;
	uint32_t m_textureHandle = 0u;

	std::list<std::unique_ptr<PlayerBullet>> m_bullets;
};
	  