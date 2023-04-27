#include "EnemyStates.h"
#include <cassert>
#include "Enemy.h"
#include "MathUtils.h"

void EnemyStateApproach::Initalize(Enemy* owner) { 
	assert(owner);
	m_owner = owner;
	FireAndReset();
}

void EnemyStateApproach::Update() {
	m_timedCalls.remove_if([](auto& timedCall) { return timedCall->IsFinished(); });
	
	for (auto& timedCall : m_timedCalls) {
		timedCall->Update();
	}

	Vector3 translation = m_owner->GetTranslation();
	translation += m_owner->GetVelocity();
	m_owner->SetTranslation(translation);
	if (translation.z < 20.0f) {
		auto newState = std::make_unique<EnemyStateLeave>();
		m_owner->ChangeState(std::move(newState));
	}
}

void EnemyStateApproach::FireAndReset() { 
	m_owner->FireBullet(); 
	auto callback = std::bind(&EnemyStateApproach::FireAndReset, this);
	auto timedCall = std::make_unique<TimedCall>(callback, kFireInterval);
	m_timedCalls.push_back(std::move(timedCall));
}

void EnemyStateLeave::Initalize(Enemy* owner) { 
	assert(owner);
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
