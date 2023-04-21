#pragma once
#include <cstdint>
#include <list>
#include <memory>
#include "TimedCall.h"

class Enemy;

// 敵の状態クラスの基底
class EnemyState {
public:
	virtual ~EnemyState() {}
	virtual void Initalize(Enemy* owner) = 0;
	virtual void Update() = 0;

protected:
	Enemy* m_owner = nullptr;
};

class EnemyStateApproach : public EnemyState {
public:
	// 発射間隔
	static constexpr int32_t kFireInterval = 20;

	void Initalize(Enemy* owner) override;
	void Update() override;

private:
	void FireAndReset();

	std::list<std::unique_ptr<TimedCall>> m_timedCalls;
};

class EnemyStateLeave : public EnemyState {
public:
	void Initalize(Enemy* owner) override;
	void Update() override;
};