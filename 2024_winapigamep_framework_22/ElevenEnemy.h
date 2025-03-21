#pragma once
#include "Enemy.h"

class ElevenEnemy : public Enemy
{
public:
	ElevenEnemy();
	virtual ~ElevenEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
	float m_warnDis = 0;
	Vec2 m_atkDir;
};