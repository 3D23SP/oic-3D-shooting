#pragma once

#include "GameDefine.h"

class CEnemy{
private:
	CMeshContainer*		m_pMesh;
	Vector3				m_Pos;
	Vector3				m_Rot;
	bool				m_bShow;

	float				m_AnimTime;

	int                 m_HP;

public:
	CEnemy();
	~CEnemy();
	void Initialize();
	void Start(const Vector3& p);
	void Update();
	void Render();
	void RenderDebug();
	void RenderDebugText(int i);
	void SetMesh(CMeshContainer* pm){ m_pMesh = pm; }
	bool GetShow(){ return m_bShow; }
	void Damage(int dmg);
	CSphere getSphere() { return CSphere(m_Pos, 0.5f); }
};