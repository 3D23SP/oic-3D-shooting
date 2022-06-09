#pragma once

#include "GameDefine.h"

// �ړ����x
#define PLAYERSHOT_SPEED	(0.4f)

class CPlayerShot{
private:
	CMeshContainer*		m_pMesh;
	Vector3				m_Pos;
	Vector3             m_Speed;
	bool				m_bShow;
	PlayerShotMode m_Move;

public:
	CPlayerShot();
	~CPlayerShot();
	void Initialize();
	void Fire(const Vector3& p);
	void Update();
	void Render();
	void SetMesh(CMeshContainer *pm){ m_pMesh = pm; }
	bool GetShow(){ return m_bShow; }

	void RenderDebug();
	CSphere GetSphere() { return CSphere(m_Pos, 0.2f); }
	void SetShow(bool bs) { m_bShow = bs; }

	void UpdateMode();
	void UpadateSingleMode();
	void UpadateDoubleMode();
	void UpdateTrppleMode();
};