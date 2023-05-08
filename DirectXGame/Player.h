#pragma once
#include "Collider.h"
#include "MathUtils.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cstdint>
#include <list>
#include <memory>

class Player : public Collider {
public:
	void Initalize(
	    const std::shared_ptr<Model>& model, const std::shared_ptr<Model>& bulletModel,
	    uint32_t texHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void OnCollision() override;
	inline Vector3 GetWorldPosition() const override {
		return GetTranslate(m_worldTransform.matWorld_);
	}

	inline const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return m_bullets; }

	inline void SetParent(const WorldTransform* parent) { m_worldTransform.parent_ = parent; }

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
