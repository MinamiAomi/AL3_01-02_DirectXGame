#pragma once
#include "MathUtils.h"

class Collider {
public:
	virtual ~Collider() {}
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() const = 0;

	inline float GetRadius() const { return m_radius; }
	inline void SetRadius(float radius) { m_radius = radius; }

private:
	float m_radius = 0;
};