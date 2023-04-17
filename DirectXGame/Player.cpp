#include "Player.h"
#include <cassert>
#include "Input.h"

void Player::Initalize(std::shared_ptr<Model> model, uint32_t texHandle) { 
	assert(model);	

	m_model = model;
	m_textureHandle = texHandle;
	m_worldTransform.Initialize();
}

void Player::Update() { 
	
	m_worldTransform.TransferMatrix();

}

void Player::Draw(const ViewProjection& viewProjection) {

	m_model->Draw(m_worldTransform, viewProjection, m_textureHandle);
}
