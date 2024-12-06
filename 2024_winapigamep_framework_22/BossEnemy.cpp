#include "pch.h"
#include "BossEnemy.h"
#include "Collider.h"
#include "AStarPathFinder.h"
#include "TimeManager.h"
#include "WaveManager.h"
#include "EnemyBullet.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GDISelector.h"
#include "ResourceManager.h"
#include "Texture.h"
#include <format>

BossEnemy::BossEnemy()
{
	m_stat.hp = 3;
	m_stat.moveSpeed = 75.f;
	m_stat.atkRange = 300.f;
	m_stat.atkCooldown = 1.2f;
	m_stat.atkDelay = 0.2f;
	m_stat.atkDamage = 4;
	m_vSize = { 240, 240 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);

	for (int i = 0; i < 4; i++)
	{
		wstring path = std::format(L"Texture\\boss{0}.bmp", i);
		m_startTexs[i] = GET_SINGLE(ResourceManager)->TextureLoad(L"BossEnemy", path);
	}

	for (int i = 0; i < 10; i++)
	{
		wstring path = std::format(L"Texture\\roll{0}.bmp", i);
		m_rollTexs[i] = GET_SINGLE(ResourceManager)->TextureLoad(L"BossEnemy", path);
	}

	for (int i = 0; i < 12; i++)
	{
		wstring path = std::format(L"Texture\\endroll{0}.bmp", i);
		m_endRollTexs[i] = GET_SINGLE(ResourceManager)->TextureLoad(L"BossEnemy", path);
	}

	m_pTex = m_startTexs[0];
	m_bossDefaultTex = m_startTexs[3];
	int width  = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	m_enemyDC = CreateCompatibleDC(m_pTex->GetTexDC());
	m_enemyBmap = CreateCompatibleBitmap(m_enemyDC, width, height);
	::SelectObject(m_enemyDC, m_enemyBmap);
}

BossEnemy::~BossEnemy()
{

	DeleteObject(m_enemyBmap);
	DeleteDC(m_enemyDC); 
}

void BossEnemy::Update()
{
}

void BossEnemy::Render(HDC _hdc)
{
	static int curAnim = 0;
	static float bossBehaviorTimer = 0;
	bossBehaviorTimer += fDT;
	if (m_bState == (int)BOSS_STATE::START)
	{
		curAnim = 0;
		if (bossBehaviorTimer >= m_startAnimFrameRate)
		{
			bossBehaviorTimer = 0;
			curAnim++;
			m_pTex = m_startTexs[curAnim];
			if (curAnim >= m_startTexLen && bossBehaviorTimer >= m_startAnimFrameRate)
			{
				m_bState = (int)BOSS_STATE::WAIT;

				m_pTex = m_bossDefaultTex;
				curAnim = 0;
				bossBehaviorTimer = 0;
			}
		}
	}
	else if (m_bState == (int)BOSS_STATE::WAIT)
	{
		if (bossBehaviorTimer >= 0.5f)
		{
			m_bState = (int)BOSS_STATE::ROLL;
			m_pTex = m_bossDefaultTex;
			curAnim = 0;
			bossBehaviorTimer = 0;
		}
	}
	else if (m_bState == (int)BOSS_STATE::ROLL)
	{
		if (bossBehaviorTimer >= m_rollAnimFrameRate)
		{
			bossBehaviorTimer = 0;
			curAnim++;
			m_pTex = m_rollTexs[curAnim];

			if (curAnim >= m_rollTexLen && bossBehaviorTimer >= m_startAnimFrameRate)
			{
				m_bState = (int)BOSS_STATE::ATTACK;
				std::uniform_int_distribution<int> typeIdx(0, m_endRollTexLen + 1 );
				m_pTex = m_endRollTexs[typeIdx(m_mt)];
				curAnim = 0;
				bossBehaviorTimer = 0;
			}
		}
	}
	else if (m_bState == (int)BOSS_STATE::ATTACK)
	{

	}

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	m_vPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2};

	::TransparentBlt(_hdc
		, (int)(m_vPos.x - (width / 2) * 8)
		, (int)(m_vPos.y - (height / 2) * 8)
		, width * 8 , height * 8,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255,0,255));
}

void BossEnemy::UpdateState()
{
}
