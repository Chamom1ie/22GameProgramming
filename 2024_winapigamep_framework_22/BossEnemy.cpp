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
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BossEnemy", L"Texture\\boss1.bmp");

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
	if (m_bState == (int)BOSS_STATE::START)
	{
		static int curAnim = 0;
	}
}

void BossEnemy::Render(HDC _hdc)
{
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
