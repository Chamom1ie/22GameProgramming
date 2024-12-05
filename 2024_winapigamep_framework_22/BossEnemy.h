#pragma once
#include "Enemy.h"
enum class BOSS_STATE
{
	START,
	WAIT,
	ROLL,
	ATTACK,
	END = 10
};
class BossEnemy :
	public Enemy
{
public:
	BossEnemy();
	virtual ~BossEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
	Vec2 m_atkDir;
	float m_rad = 0.f;
	HDC m_enemyDC;
	HBITMAP m_enemyBmap;
	int patternCounter = 0;
	int m_bState = (int)BOSS_STATE::START;
	Texture* m_StartTexs[4];
	Texture* m_rollTexs[10];
	Texture* m_endRollTexs[4];
};