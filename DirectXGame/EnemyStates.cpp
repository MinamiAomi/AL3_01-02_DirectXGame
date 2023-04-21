#include "EnemyStates.h"
#include "Enemy.h"
#include "MathUtils.h"

void EnemyStateApproach::Update() {
	Vector3 translation = m_owner->GetTranslation();
	translation += m_owner->GetVelocity();
	m_owner->SetTranslation(translation);
	if (translation.z < 0.0f) {
		auto newState = std::make_unique<EnemyStateLeave>(m_owner);
		m_owner->ChangeState(std::move(newState));
	}
}
void EnemyStateLeave::Update() {
	Vector3 translation = m_owner->GetTranslation();
	translation += -m_owner->GetVelocity();
	m_owner->SetTranslation(translation);
	if (translation.z > 100.0f) {
		auto newState = std::make_unique<EnemyStateApproach>(m_owner);
		m_owner->ChangeState(std::move(newState));
	}
}
