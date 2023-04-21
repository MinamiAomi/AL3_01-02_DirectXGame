#pragma once
#include <cstdint>

class Enemy;

// 敵の状態クラスの基底
class EnemyState {
public:
	virtual ~EnemyState() {}
	virtual void Initalize(Enemy* owner) = 0;
	virtual void Update() = 0;

protected:
	Enemy* m_owner;
};

class EnemyStateApproach : public EnemyState {
public:
	// 発射間隔
	static constexpr int32_t kFireInterval = 20;

	void Initalize(Enemy* owner) override;
	void Update() override;

private:
	int32_t m_fireTimer = 0;
};

class EnemyStateLeave : public EnemyState {
public:
	void Initalize(Enemy* owner) override;
	void Update() override;
};