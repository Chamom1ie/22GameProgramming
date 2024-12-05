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
	/*map<const int, ENEMY_TYPE[]> rollEnds = { 
		{1,{ENEMY_TYPE::RANGE, ENEMY_TYPE::MELEE, ENEMY_TYPE::BOSS}}, 
		{2,{ENEMY_TYPE::RANGE, ENEMY_TYPE::RANGE, ENEMY_TYPE::RANGE}} };*/

	Texture* m_startTexs[4];
	Texture* m_rollTexs[10];
	Texture* m_endRollTexs[12];
	Texture* m_bossDefaultTex;
	int m_startTexLen = 3;
	int m_rollTexLen = 9;
	int m_endRollTexLen = 11;
	float m_startAnimFrameRate = 0.35f;
	float m_rollAnimFrameRate = 0.1f;

	std::random_device m_rd;
	std::mt19937 m_mt;
};