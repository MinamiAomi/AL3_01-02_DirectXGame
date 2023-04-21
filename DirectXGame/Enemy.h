#pragma once
#include <cstdint>
#include <memory>
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
public:
	void Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform m_worldTransform;
	Vector3 m_velocity{};
	std::shared_ptr<Model> m_model;
	uint32_t m_texutreHandle = 0u;
};
