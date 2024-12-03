#pragma once
#include "Enemy.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy();
	virtual ~RangeEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
	float m_warnDis;
	Vec2 m_atkDir;
};