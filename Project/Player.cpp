#include "Player.h"

/**
 * コンストラクタ
 */
CPlayer::CPlayer() :
m_Mesh(),
m_Pos(0.0f,0.0f,0.0f),
m_RotZ(0.0f),
m_Speed(1),
m_RotSpeed(1),
m_bDead(false),
m_ShotMesh(),
m_ShotArray(),
m_ShotWait(){
}

/**
 * デストラクタ
 */
CPlayer::~CPlayer(){
}

/**
 * 読み込み
 */
bool CPlayer::Load(void){
	// メッシュの読み込み
	m_Mesh.Load("player.mom");
	m_ShotMesh.Load("pshot.mom");
		return false;

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetMesh(&m_ShotMesh);
	}

	return true;
}

/**
 * 初期化
 */
void CPlayer::Initialize(void){
	m_Pos = Vector3(0.0f, 0.0f, -FIELD_HALF_Z + 2.0f);
	m_RotZ = 0;
	m_bDead = false;
	m_SMode = PlayerShotMove::MODE_DOUBLE;
	m_SubMode = PlayerShotSubMode::MODE_DIRECT

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}

/**
 * 更新
 */
void CPlayer::Update(void){
	if (m_bDead)
	{
		return;
	}
	//回転方向
	float roll = 0;
	float m_Speed = PLAYER_SPEED;
	float RotSpeed = MOF_ToRadian(10);
	//キーボードでの移動
	if (g_pInput->IsKeyHold(MOFKEY_SPACE))
	{
		m_Speed *= 3;
		//RotSpeed *= 4;
	}
	if (g_pInput->IsKeyHold(MOFKEY_LEFT))
	{
		m_Pos.x = max(m_Pos.x - m_Speed, -FIELD_HALF_X);
		roll -= MOF_MATH_PI;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
	{
		m_Pos.x = min(m_Pos.x + m_Speed, FIELD_HALF_X);
		roll += MOF_MATH_PI;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP))
	{
		m_Pos.z = min(m_Pos.z + m_Speed, FIELD_HALF_Z);
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN))
	{
		m_Pos.z = max(m_Pos.z - m_Speed, -FIELD_HALF_Z);
	}
	//回転
	//float RotSpeed = MOF_ToRadian(10);
	if (roll == 0)
	{
		RotSpeed = min(abs(m_RotZ) * 0.1f, RotSpeed);
	}
	if (abs(m_RotZ) <= RotSpeed || signbit(m_RotZ) != signbit(roll))
	{
		m_RotZ += roll;
	}
	m_RotZ -= copysignf(min(RotSpeed, abs(m_RotZ)), m_RotZ);

	//弾の発射
	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyHold(MOFKEY_LSHIFT))
		{
			for (int cnt = 0; cnt < 3; cnt++)
			{
				for (int i = 0; i < PLAYERSHOT_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow()) { continue; }
					CVector3 ShotPos(0.4f * (cnt * 2 - 1), 0, 0);
					ShotPos.RotationZ(m_RotZ);
					ShotPos += m_Pos;
					m_ShotWait = PLAYERSHOT_WAIT;
					m_ShotArray[i].Fire(ShotPos);
					break;
				}
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}

}
/*
*
*敵の当たり判定
*
*/
void CPlayer::CollisionEnemy(CEnemy & ene) {
	if (!ene.GetShow())
	{
		return;
	}
	CSphere ps = GetSphere();
	CSphere es = ene.GetSphere();
	if (ps.CollisionSphere(es))
	{
		m_bDead = true;
	}
	//弾との判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_ShotArray[i].GetShow())
		{
			continue;
		}
		CSphere ss = m_ShotArray[i].GetSphere();
		if (ss.CollisionSphere(es))
		{
			ene.Damage(1);
			m_ShotArray[i].SetShow(false);
			break;
		}
	}
}

/**
 * 描画
 */
void CPlayer::Render(void){
	if (m_bDead)
	{
		return;
	}
	//ワールド行列作成
	CMatrix44 matworld;
	matworld.RotationZ(m_RotZ);
	matworld.SetTranslation(m_Pos);
	//メッシュの描画
	m_Mesh.Render(matworld);

	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}
}

/**
*デバッグ描画
*/
void CPlayer::RenderDebug(void) {
	//非表示
	if (!GetShow())
	{
		return;
	}
	//当たり判定の表示
	CGraphicsUtilities::RenderSphere(GetSphere(), Vector4(1, 0, 0, 0, 3.0f));
}

/**
 * デバッグ文字描画
 */
void CPlayer::RenderDebugText(void){
	// 位置の描画
	CGraphicsUtilities::RenderString(10,40,MOF_XRGB(0,0,0),
			"プレイヤー位置 X : %.1f , Y : %.1f , Z : %.1f",m_Pos.x,m_Pos.y,m_Pos.z);
}

/**
 * 解放
 */
void CPlayer::Release(void){
	m_Mesh.Release();
	m_ShotMesh.Release();
}