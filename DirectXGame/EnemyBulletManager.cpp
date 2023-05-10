#include "EnemyBulletManager.h"
#include "TextureManager.h"
#include <cassert>

void EnemyBulletManager::Initalize(const std::shared_ptr<Model>& bulletModel) {
	assert(bulletModel);
	m_bulletModel = bulletModel;
	m_textureHandle = TextureManager::GetInstance()->Load("red.png");
}

void EnemyBulletManager::Update() {
	// 弾を削除
	m_bullets.remove_if([](auto& bullet) { return bullet->IsDead(); });

	// 弾を更新
	for (auto& bullet : m_bullets) {
		bullet->Update();
	}
}

void EnemyBulletManager::Draw(const ViewProjection& viewProjection) {
	for (auto& bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}
}

EnemyBullet& EnemyBulletManager::AddBullet() {
	auto bullet = new EnemyBullet;
	bullet->SetPlayer(m_player);
	bullet->SetModel(m_bulletModel);
	bullet->SetTextureHandle(m_textureHandle);
	m_bullets.emplace_back(bullet);
	return *bullet;
}
