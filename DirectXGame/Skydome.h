#pragma once
#include <memory>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Skydome {
public:
	void Initalize(const std::shared_ptr<Model>& model);
	void Update();
	void Draw(const ViewProjection& viewProj);

private:	
	WorldTransform m_worldTransform;
	std::shared_ptr<Model> m_model;
};
