#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:
	void Initalize(const Vector3& pos, const Vector3& rot);
	void Update();
	void Draw();

	const ViewProjection& GetViewProjection() const { return m_viewProjection; }
	const WorldTransform& GetWorldTransform() const { return m_worldTransform; }

private:
	WorldTransform m_worldTransform;
	ViewProjection m_viewProjection;

};
