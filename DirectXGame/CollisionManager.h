#pragma once
#include <vector>
#include "Collider.h"

class CollisionManager {
public:
	void AddCollider(Collider* collider) { m_colliders.emplace_back(collider); }
	void ClearColliders() { m_colliders.clear(); }
	void CheckAllCollisions();

private:
	std::vector<Collider*> m_colliders;
};
