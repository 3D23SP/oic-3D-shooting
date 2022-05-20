#pragma once

#include "GameDefine.h"
#include "PlayerShot.h"

// �ړ����x
#define PLAYER_SPEED		(0.1f)

//�e�̔��ˌ��x
#define PLAYERSHOT_COUNT (40)

//�e�̔��ˊԊu
#define PLAYERSHOT_WAIT (5)

class CPlayer{
private:
	CMeshContainer	m_Mesh;
	CVector3		m_Pos;
	float			m_RotZ;
	int m_Speed;
	float m_RotSpeed;
	CMeshContainer m_ShotMesh;
	CPlayerShot m_ShotArray[PLAYERSHOT_COUNT];
	int m_ShotWait;
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
};