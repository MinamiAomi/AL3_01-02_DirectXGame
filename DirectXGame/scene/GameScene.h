#pragma once
#include <memory>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "CatmullRomSpline.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// リソース
	std::shared_ptr<Model> m_fighterModel;
	std::shared_ptr<Model> m_bulletModel;
	std::shared_ptr<Model> m_skydomeModel;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	const ViewProjection* m_curViewProj = nullptr;
	std::unique_ptr<CollisionManager> m_collisionManager; 

	// オブジェクト
	std::unique_ptr<RailCamera> m_railCamera; 
	std::shared_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy;
	std::unique_ptr<Skydome> m_skydome;

//#ifdef _DEBUG
	// デバッグ用
	std::unique_ptr<DebugCamera> m_debugCamera;
	bool m_isDebugCameraActive = false;

	CatmullRomSpline m_catmullRomSpline;
	//#endif
};
