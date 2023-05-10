#include "CollisionManager.h"
#include "Collider.h"

void CollisionManager::CheckAllCollisions() {
	auto itrA = m_colliders.begin();
	for (; itrA != m_colliders.end(); ++itrA) {
		auto itrB = itrA;
		++itrB;
		for (; itrB != m_colliders.end(); ++itrB) {

			if (!((*itrA)->GetCollisionAttribute() & (*itrB)->GetCollisionMask()) ||
			    !((*itrB)->GetCollisionAttribute() & (*itrA)->GetCollisionMask())) {
				continue;
			}

			Vector3 posA = (*itrA)->GetWorldPosition();
			Vector3 posB = (*itrB)->GetWorldPosition();
			float radA = (*itrA)->GetRadius();
			float radB = (*itrB)->GetRadius();

			if (LengthSquare(posB - posA) <= (radA + radB) * (radA + radB)) {
				(*itrA)->OnCollision();
				(*itrB)->OnCollision();
			}
		}
	}
}
