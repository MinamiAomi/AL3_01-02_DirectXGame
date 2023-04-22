#include "Skydome.h"
#include <cassert>

void Skydome::Initalize(const std::shared_ptr<Model>& model) { 
	assert(model);
	m_model = model; 
	m_worldTransform.Initialize();
	m_worldTransform.scale_ = {100.0f, 100.0f, 100.0f};
	m_worldTransform.UpdateMatrix();
}

void Skydome::Update() {}

void Skydome::Draw(const ViewProjection& viewProj) { m_model->Draw(m_worldTransform, viewProj); }
