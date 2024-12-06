#pragma once
#include "Enemy.h"

enum class BOSS_STATE
{
	START,
	WAIT,
	ROLL,
	ATTACK,
	Jackpot_1,
	Jackpot_2,
	Jackpot_3,
	Jackpot_4,
	Jackpot_5,
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

	#pragma region 보스 정보
	int m_forceJackpotCnt = 0;
	int patternIdx;
	int m_jackPotIdx;
	int m_bState = (int)BOSS_STATE::START;
	ENEMY_TYPE texByEnemies[12][3]{
		{ENEMY_TYPE::Orage, ENEMY_TYPE::XSlide, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Eleven, ENEMY_TYPE::XSlide, ENEMY_TYPE::Doll},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::Doll, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Doll, ENEMY_TYPE::Eleven, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::XSlide, ENEMY_TYPE::Doll},
		{ENEMY_TYPE::Eleven, ENEMY_TYPE::Doll, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::XSlide, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Eleven, ENEMY_TYPE::Doll, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::Eleven, ENEMY_TYPE::XSlide},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::Tradian, ENEMY_TYPE::XSlide},
		{ENEMY_TYPE::Orage, ENEMY_TYPE::Eleven, ENEMY_TYPE::Tradian},
		{ENEMY_TYPE::Eleven, ENEMY_TYPE::XSlide, ENEMY_TYPE::Orage},
	};
	#pragma endregion


	#pragma region 짭 애니메이터
	Texture* m_startTexs[4];
	Texture* m_rollTexs[10];
	Texture* m_endRollTexs[12];
	Texture* m_jackpotTexs[5];
	Texture* m_bossDefaultTex;

	int m_startTexLen = 3;
	int m_rollTexLen = 9;
	int m_endRollTexLen = 11;
	int m_jackpotTexLen = 4;
	float m_startAnimFrameRate = 0.65f;
	float m_rollAnimFrameRate = 0.08f;
	float m_attackCooldown= 0.5f;
	#pragma endregion

	std::random_device m_rd;
	std::mt19937 m_mt;
};