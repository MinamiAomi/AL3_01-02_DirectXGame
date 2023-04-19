#pragma once
#include <cstdint>
#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class PlayerBullet {
public:
	void Initalize(std::shared_ptr<Model> model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProj);

	void DebugUI();

private:
	WorldTransform m_worldTransform;
	std::shared_ptr<Model> m_model;
	uint32_t m_textureHandle = 0u;
};
