#include "EnemyStates.h"
#include "Enemy.h"
#include "MathUtils.h"

void EnemyStateApproach::Initalize(Enemy* owner) { 
	m_owner = owner;
	m_fireTimer = kFireInterval; 
}

void EnemyStateApproach::Update() {
	if (--m_fireTimer <= 0) {
		m_owner->FireBullet();
		m_fireTimer = kFireInterval;
	}
	
	Vector3 translation = m_owner->GetTranslation();
	translation += m_owner->GetVelocity();
	m_owner->SetTranslation(translation);
	if (translation.z < 20.0f) {
		auto newState = std::make_unique<EnemyStateLeave>();
		m_owner->ChangeState(std::move(newState));
	}
}
void EnemyStateLeave::Initalize(Enemy* owner) { 
	m_owner = owner;
}

void EnemyStateLeave::Update() {
	Vector3 translation = m_owner->GetTranslation();
	translation += -m_owner->GetVelocity();
	m_owner->SetTranslation(translation);
	if (translation.z > 60.0f) {
		auto newState = std::make_unique<EnemyStateApproach>();
		m_owner->ChangeState(std::move(newState));
	}
}
