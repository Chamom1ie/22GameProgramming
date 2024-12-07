#include "pch.h"
#include "OrageEnemy.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"

OrageEnemy::OrageEnemy()
{
	m_stat.hp = 5;
	m_stat.moveSpeed = 100.f;
	m_stat.atkRange = 50.f;
	m_stat.atkCooldown = 1.f;
	m_stat.atkDamage = 5;
	m_vSize = { 30, 30 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"OrageEnemy", L"Texture\\Orage.bmp");
}

OrageEnemy::~OrageEnemy()
{
}

void OrageEnemy::Update()
{
}

void OrageEnemy::Render(HDC _hdc)
{
}

void OrageEnemy::UpdateState()
{
}
