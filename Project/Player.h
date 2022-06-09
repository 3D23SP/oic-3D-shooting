#pragma once

#include "GameDefine.h"
#include "PlayerShot.h"
#include "Enemy.h"

// ˆÚ“®‘¬“x
#define PLAYER_SPEED		(0.1f)

//’e‚Ì”­ŽËŒÀ“x
#define PLAYERSHOT_COUNT (40)

//’e‚Ì”­ŽËŠÔŠu
#define PLAYERSHOT_WAIT (5)

class CPlayer{
private:
	CMeshContainer	m_Mesh;
	CVector3		m_Pos;
	float			m_RotZ;
	PlayerMove      m_Move;

	CMeshContainer m_ShotMesh;
	CPlayerShot m_ShotArray[PLAYERSHOT_COUNT];
	int m_ShotWait;

	PlayerShotMode m_ShotMode;
	PlayerShotSubMode m_SubMode;

	bool m_bDead;

	int m_Speed;
	float m_RotSpeed;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebugText();
	const CVector3 GetPosition(){ return m_Pos; }
	void Release();
	PlayerMove GetMove(){ return m_Move; }

	void RenderDebug();
	CSphere GetSphere() { return CSphere(m_Pos, 0.4f); }

	void CollisionEnemy(CEnemy& ene);
	bool IsDead(){ return m_bDead; }

	void UpdateMode();
	void UpdateSingleMode();
	void UpdateDoubleMode();
	void UpdateTrippleMode();
};