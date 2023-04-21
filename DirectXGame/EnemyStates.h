#pragma once

class Enemy;

// 敵の状態クラスの基底
class EnemyState {
public:
	EnemyState(Enemy* owner) : m_owner(owner) {}
	virtual ~EnemyState() {}
	virtual void Update() = 0;

protected:
	Enemy* m_owner;
};

class EnemyStateApproach : public EnemyState {
public:
	EnemyStateApproach(Enemy* owner) : EnemyState(owner) {}
	void Update();
};

class EnemyStateLeave : public EnemyState {
public:
	EnemyStateLeave(Enemy* owner) : EnemyState(owner) {}
	void Update();
};