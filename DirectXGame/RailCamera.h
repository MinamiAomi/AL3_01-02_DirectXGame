#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "CatmullRomSpline.h"

class RailCamera {
public:
	static const uint32_t kLoopTime = 1200 * 3;

	void Initalize(const Vector3& pos, const Vector3& rot);
	void Update();
	void Draw();

	const ViewProjection& GetViewProjection() const { return m_viewProjection; }
	const WorldTransform& GetWorldTransform() const { return m_worldTransform; }

private:
	WorldTransform m_worldTransform;
	ViewProjection m_viewProjection;

	CatmullRomSpline m_rail;
	uint32_t m_moveTime = 0;
};
