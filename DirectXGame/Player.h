#pragma once
#include <cstdint>
#include <memory>
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Player {
public:
	void Initalize(std::shared_ptr<Model> model, uint32_t texHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform m_worldTransform;
	std::shared_ptr<Model> m_model = nullptr;
	uint32_t m_textureHandle = 0u;

};
	  