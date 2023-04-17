#include "GameScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	m_viewProj.Initialize();

	m_model.reset(Model::CreateFromOBJ("cube"));

	m_player = std::make_unique<Player>();
	m_player->Initalize(m_model, TextureManager::Load("ziki.png"));

#ifdef _DEBUG
	m_debugCamera = std::make_unique<DebugCamera>(
	    dxCommon_->GetBackBufferWidth(), dxCommon_->GetBackBufferHeight());
	m_debugCamera;
	m_isDebugCameraActive = false;

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&m_viewProj);
#endif
}

void GameScene::Update() {
	m_player->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_TAB)) {
		m_isDebugCameraActive ^= true;
	}
	if (m_isDebugCameraActive) {
		m_debugCamera->Update();
		m_viewProj.matView = m_debugCamera->GetViewProjection().matView;
		m_viewProj.matProjection = m_debugCamera->GetViewProjection().matProjection;
		m_viewProj.TransferMatrix();

#pragma region デバッグ用ImGuiウィンドウ
		ImGui::Begin("Debug");
		ImGui::SetWindowPos({0, 520});
		ImGui::SetWindowSize({300, 200});
		static bool axisVisible = true;
		ImGui::Checkbox("AxisVisible", &axisVisible);
		AxisIndicator::GetInstance()->SetVisible(axisVisible);
		ImGui::End();
#pragma endregion

	} else {
		m_viewProj.UpdateMatrix();
	}
#endif
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
	m_player->Draw(m_viewProj);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
