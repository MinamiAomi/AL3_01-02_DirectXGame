#include "Enemy.h"
#include <cassert>
#include "Player.h"
#include "ImGuiManager.h"
#include "CollisionCofig.h"

void Enemy::Initalize(
    const std::shared_ptr<Player>& player, 
	const std::shared_ptr<Model>& model,
    const std::shared_ptr<Model>& bulletModel, 
	uint32_t texHandle) {
	assert(player);
	assert(model);
	assert(bulletModel);

	m_player = player;
	m_model = model;
	m_bulletModel = bulletModel;
	m_texutreHandle = texHandle;
	m_worldTransform.Initialize();
	m_velocity = {0.0f, 0.0f, -0.2f};
	m_worldTransform.translation_ = {5.0f, 2.0f, 50.0f};
	m_worldTransform.rotation_ = {0.0f, Math::ToRad(180.0f), 0.0f};
	m_worldTransform.UpdateMatrix();
	ChangeState(std::make_unique<EnemyStateApproach>());

	SetRadius(1.0f);
	SetCollisionAttribute(CollisionConfig::kAttributeEnemy);
	SetCollisionMask(~CollisionConfig::kAttributeEnemy);
}

void Enemy::Update() {
	// 弾を削除
	m_bullets.remove_if([](auto& bullet) { return bullet->IsDead() ? true : false; });

	m_state->Update();

	m_worldTransform.UpdateMatrix();
	// 弾を更新
	for (auto& bullet : m_bullets) {
		bullet->Update();
	}

	ImGui::SetNextWindowPos({0, 110}, ImGuiCond_Once);
	ImGui::SetNextWindowSize({300, 100}, ImGuiCond_Once);
	ImGui::Begin("EnemyBulletConfig");
	ImGui::SliderFloat("Slerp ratio", &EnemyBullet::slerpRatio, 0.0f, 1.0f);
	ImGui::End();


}

void Enemy::Draw(const ViewProjection& viewProjection) {
	m_model->Draw(m_worldTransform, viewProjection, m_texutreHandle);

	for (auto& bullet : m_bullets) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::OnCollision() {}

void Enemy::ChangeState(std::unique_ptr<EnemyState> state) {
	m_state = std::move(state);
	m_state->Initalize(this);
}

void Enemy::FireBullet() {
	const float kBulletSpeed = 1.0f;

	Vector3 playerPosition = m_player->GetWorldPosition();
	Vector3 enemyPosition = GetTranslate(m_worldTransform.matWorld_);
	Vector3 velocity = playerPosition - enemyPosition;
	velocity = Normalize(velocity) * kBulletSpeed;

	auto newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initalize(m_player, m_bulletModel, m_worldTransform.translation_, velocity);

	m_bullets.push_back(std::move(newBullet));
}
