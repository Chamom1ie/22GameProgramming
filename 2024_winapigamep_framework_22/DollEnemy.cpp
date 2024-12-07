#include "pch.h"
#include "DollEnemy.h"
#include "WaveManager.h"
#include "ResourceManager.h"

DollEnemy::DollEnemy()
{
	m_stat.hp = 5;
	m_stat.moveSpeed = 100.f;
	m_stat.atkRange = 50.f;
	m_stat.atkCooldown = 1.f;
	m_stat.atkDamage = 5;
	m_vSize = { 30, 30 };
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"DollEnemy", L"Texture\\Doll.bmp");
}

DollEnemy::~DollEnemy()
{
	GET_SINGLE(WaveManager)->Push(ENEMY_TYPE::Doll, new DollEnemy);
}
