#include "pch.h"
#include "TradianEnemy.h"
#include "WaveManager.h"
#include "ResourceManager.h"

TradianEnemy::TradianEnemy()
{
	m_stat.hp = 5;
	m_stat.moveSpeed = 100.f;
	m_stat.atkRange = 50.f;
	m_stat.atkCooldown = 1.f;
	m_stat.atkDamage = 5;
	m_vSize = { 30, 30 };
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"TradianEnemy", L"Texture\\Tradian.bmp");
}

TradianEnemy::~TradianEnemy()
{
	GET_SINGLE(WaveManager)->Push(ENEMY_TYPE::Tradian, new TradianEnemy);
}
