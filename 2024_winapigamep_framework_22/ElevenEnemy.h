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
	float m_warnDis;
	Vec2 m_atkDir;
};