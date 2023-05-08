#include "EnemyManager.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

void EnemyManager::Initalize(const std::shared_ptr<Model>& model) {
	assert(model);
	m_enemyModel = model;
	m_textureHandle = TextureManager::Load("enemy.png");
	LoadEnemyPopData();
}

void EnemyManager::Update() {
	m_enemys.remove_if([](auto& enemy) { return enemy->IsDead() ? true : false; });

	UpdateEnemyPopData();

	// 弾を更新
	for (auto& enemy : m_enemys) {
		enemy->Update();
	}
}

void EnemyManager::Draw(const ViewProjection& viewProjection) {
	for (auto& enemy : m_enemys) {
		enemy->Draw(viewProjection);
	}
}

Enemy& EnemyManager::AddEnemy() {
	auto enemy = new Enemy;
	enemy->SetPlayer(m_player);
	enemy->SetBulletManager(m_bulletManager);
	enemy->SetTextureHandle(m_textureHandle);
	enemy->SetModel(m_enemyModel);
	m_enemys.emplace_back(enemy);
	return *enemy;
}

void EnemyManager::LoadEnemyPopData() {
	std::ifstream file;
	file.open("Resources/EnemyControlScript.csv");
	assert(file.is_open());

	m_enemyPopCommands << file.rdbuf();

	file.close();
}

void EnemyManager::UpdateEnemyPopData() {
	if (m_isWaitingPop) {
		m_waitTime--;
		if (m_waitTime <= 0) {
			m_isWaitingPop = false;
		}
		return;
	}

	std::string line;

	while (std::getline(m_enemyPopCommands, line)) {
		std::istringstream lineStream(line);

		std::string word;
		std::getline(lineStream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("POP") == 0) {
			// x座標
			std::getline(lineStream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));
			// y座標
			std::getline(lineStream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));
			// z座標
			std::getline(lineStream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			auto& enemy = AddEnemy();
			enemy.Initalize({x, y, z});
		} else if (word.find("WAIT") == 0) {
			std::getline(lineStream, word, ',');
			// 待機開始
			m_isWaitingPop = true;
			m_waitTime = std::atoi(word.c_str());
			// コマンドループを抜ける
			break;
		}
	}
}
