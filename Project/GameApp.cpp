/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include "Player.h"
#include "Stage.h"
#include "Stage1.h"

CCamera gCamera;
CDirectionalLight gLight;
CPlayer gPlayer;
#define ENEMY_COUNT (20)
CEnemy gEnemyArray[ENEMY_COUNT];
bool gbDebug = false;
CStage gStage;

CVector3 gCameraPosition;
CVector3 TargetPosition;
CVector3 gUpVector;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	gCamera.SetViewPort();
	gCamera.LookAt(Vector3(0, 6.0f, -17.0f), Vector3(0, 0, -10), Vector3(0, 1, 0));
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f, 0.01f, 1000.0f);
	CGraphicsUtilities::SetCamera(&gCamera);

	gLight.SetDirection(Vector3(-1, -2, 1.5f));
	gLight.SetDiffuse(MOF_COLOR_WHITE);
	gLight.SetAmbient(MOF_COLOR_WHITE);
	gLight.SetSpeculer(MOF_COLOR_WHITE);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	gPlayer.Load();
	gStage.Load();
	gPlayer.Initialize();
	gStage.Initialize(&gStg1EnemyStart);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Initialize();
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	gPlayer.Update();

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Update();
	}

	//敵との当たり判定
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gPlayer.CollisionEnemy(gEnemyArray[i]);
	}

	gStage.Update(gEnemyArray,ENEMY_COUNT);

	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = ((gbDebug) ? false : true);
	}

	//ゲームオーバーでEnter表示
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && gPlayer.IsDead())
	{
		//ゲーム内オブジェクトの初期化
		gPlayer.Initialize();
		gStage.Initialize(&gStg1EnemyStart);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].Initialize();
		}
	}

	float posX = gPlayer.GetPosition().x * 0.4f;
	CVector3 cpos = gCamera.GetViewPosition();
	CVector3 tpos = gCamera.GetTargetPosition();
	CVector3 vup = CVector3(0, 1, 0);
	cpos.x = posX;
	tpos.x = posX;
	vup.RotationZ(gPlayer.GetPosition().x / FIELD_HALF_X * MOF_ToRadian(10.0f));
	gCamera.LookAt(cpos, tpos, vup);
	gCamera.Update();

	return TRUE;
}

/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画処理
	g_pGraphics->RenderStart();
	// 画面のクリア
	g_pGraphics->ClearTarget(0.65f,0.65f,0.67f,0.0f,1.0f,0);

	g_pGraphics->SetDepthEnable(TRUE);

	gPlayer.Render();
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		gEnemyArray[i].Render();
	}

	gStage.Render();

	if (gbDebug)
	{
		gPlayer.RenderDebug();

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].RenderDebug();
		}

		CMatrix44 matworld;
		matworld.Scaling(FIELD_HALF_X * 2, 1, FIELD_HALF_Z * 2);
		CGraphicsUtilities::RenderPlane(matworld, Vector4(1, 1, 1, 0.4f));
	}

	g_pGraphics->SetDepthEnable(FALSE);

	if (gbDebug)
	{
		gPlayer.RenderDebugText();
		gStage.RenderDebugText();

		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			gEnemyArray[i].RenderDebugText(i);
		}
	}

	if (gPlayer.IsDead())
	{
		CGraphicsUtilities::RenderString(240, 350, MOF_COLOR_RED, "ゲームオーバー : Enterキーでもう一度最初から");
	}

	// 描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gPlayer.Release();
	gStage.Release();
	return TRUE;
}