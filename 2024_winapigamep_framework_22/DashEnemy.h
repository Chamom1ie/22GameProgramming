#pragma once
#include "Enemy.h"
class DashEnemy : public Enemy
{
public:
	DashEnemy();
	virtual ~DashEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
	Vec2 m_atkDir;
	float m_rad = 0.f;
	HDC m_enemyDC;
	HBITMAP m_enemyBmap;
};