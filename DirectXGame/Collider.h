#pragma once
#include <cstdint>
#include "MathUtils.h"

class Collider {
public:
	virtual ~Collider() {}
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() const = 0;

	inline float GetRadius() const { return m_radius; }
	inline void SetRadius(float radius) { m_radius = radius; }
	inline uint32_t GetCollisionAttribute() const { return m_collisionAttribute; }
	inline void SetCollisionAttribute(uint32_t attribute) { m_collisionAttribute = attribute; }
	inline uint32_t GetCollisionMask() const { return m_collisionMask; }
	inline void SetCollisionMask(uint32_t mask) { m_collisionMask = mask; }

private:
	float m_radius = 0;
	uint32_t m_collisionAttribute = 0xFFFFFFFF;
	uint32_t m_collisionMask = 0xFFFFFFFF;
};