#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MyMath.h"


GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);

	// テクスチャを読み込み
	textureHandle_ = TextureManager::Load("mario.jpg");
	// スプライトを生成
	sprite_.reset(Sprite::Create(textureHandle_, {100, 50}));
	// モデルを生成
	model_.reset(Model::Create());
	// ワールドトランスフォームを初期化
	worldTransform_.Initialize();
	// ビュープロジェ行列を初期化
	viewProjection_.Initialize();
	// ライン描画が参照するビュープロジェクションを指定
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	// サウンドデータを読み込み
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");
	// 音声再生
	soundPlayHandle_ = audio_->PlayWave(soundDataHandle_, true, 0.05f);

	AxisIndicator::GetInstance()->Initialize();
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	AxisIndicator::GetInstance()->SetVisible(true);
}

void GameScene::Update() { 
	Vector2 position = sprite_->GetPosition();
	position += {2.0f, 1.0f};
	sprite_->SetPosition(position);

	// スペースキーで音を止める
	if (input_->TriggerKey(DIK_SPACE)) {
		audio_->StopWave(soundPlayHandle_);
	}

	{
		static float inputFloat3[3] = {0.0f, 0.0f, 0.0f};

		ImGui::Begin("Debug");
		ImGui::SetWindowPos(ImVec2(0.0f,0.0f));
		ImGui::SetWindowSize(ImVec2(320.0f,80.0f));
		ImGui::InputFloat3("InputFloat3", inputFloat3);
		ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
		ImGui::End();
	}

	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	AxisIndicator::GetInstance()->Draw();

	PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->DrawLine3d(Vector3::Zero, Vector3::UnitX, Color::Black);

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
