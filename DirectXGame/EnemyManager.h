#pragma once
#include <list>
#include <memory>
#include <sstream>
#include "Enemy.h"
#include "Model.h"
#include "ViewProjection.h"
#include "Player.h"
#include "EnemyBulletManager.h"

class EnemyManager {
public:
	void Initalize(const std::shared_ptr<Model>& model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	Enemy& AddEnemy();
	inline const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return m_enemys; }

	void SetPlayer(const std::shared_ptr<Player>& player) { m_player = player; }
	void SetBulletManager(const std::shared_ptr<EnemyBulletManager>& bulletManager) {
		m_bulletManager = bulletManager;
	}

private:
	void LoadEnemyPopData();
	void UpdateEnemyPopData();

	std::list<std::unique_ptr<Enemy>> m_enemys;
	std::shared_ptr<Model> m_enemyModel;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<EnemyBulletManager> m_bulletManager;
	uint32_t m_textureHandle = 0u;

	std::stringstream m_enemyPopCommands;
	bool m_isWaitingPop;
	int32_t m_waitTime;
};
