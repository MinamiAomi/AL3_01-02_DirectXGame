#pragma once
#include <memory>
#include <list>
#include "EnemyBullet.h"
#include "ViewProjection.h"
#include "Model.h"
#include "Player.h"

class EnemyBulletManager {
public:
	void Initalize(const std::shared_ptr<Model>& bulletModel);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	EnemyBullet& AddBullet();
	inline const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return m_bullets; }

	void SetPlayer(const std::shared_ptr<Player>& player) { m_player = player; }

private:
	std::list<std::unique_ptr<EnemyBullet>> m_bullets;
	std::shared_ptr<Model> m_bulletModel;
	std::shared_ptr<Player> m_player;
	uint32_t m_textureHandle = 0u;
};
