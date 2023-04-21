#pragma once
#include <cstdint>
#include <memory>
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
public:
	enum class Phase {
		Approach,	// 接近する
		Leave		// 離脱する
	};

	void Initalize(std::shared_ptr<Model> model, uint32_t texHandle, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	// 行動パターン関数テーブル
	static void (Enemy::*s_phaseFuncTable[])();

	void ApproachPhase();
	void LeavePhase();

	WorldTransform m_worldTransform;
	Vector3 m_velocity{};

	Phase m_phase = Phase::Approach;	
	
	std::shared_ptr<Model> m_model;
	uint32_t m_texutreHandle = 0u;
};
