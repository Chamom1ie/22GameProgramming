#include "pch.h"
#include "ElevenEnemy.h"
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

ElevenEnemy::ElevenEnemy()
{
	m_stat.hp = 3;
	m_stat.moveSpeed = 75.f;
	m_stat.atkRange = 200.f;
	m_stat.atkCooldown = 1.5f;
	m_stat.atkDelay = 0.5f;
	m_stat.atkDamage = 5;
	m_vSize = { 20, 20 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"RangeEnemy", L"Texture\\Eleven.bmp");
}

ElevenEnemy::~ElevenEnemy()
{
}

void ElevenEnemy::Update()
{
	UpdateState();
}

void ElevenEnemy::Render(HDC _hdc)
{
	HPEN newPen = CreatePen(PS_INSIDEFRAME, 2, RGB(255, 50, 50));
	HPEN oldPen = (HPEN)SelectObject(_hdc, newPen);

	float len = m_warnDis / m_atkDir.Length();
	MoveToEx(_hdc, m_vPos.x, m_vPos.y, nullptr);
	LineTo(_hdc, m_vPos.x + m_atkDir.x * len, m_vPos.y + m_atkDir.y * len);
	DeleteObject(newPen);
	SelectObject(_hdc, oldPen);

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(m_vPos.x - width / 2)
		, (int)(m_vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

void ElevenEnemy::UpdateState()
{
	AStarPathFinder* pathFinder = GetComponent<AStarPathFinder>();
	Vec2 targetPos = m_target->GetPos();
	Vec2 dir = (targetPos - m_vPos).Normalize();
	float dis = (targetPos - m_vPos).Length();
	switch (m_state)
	{
	case EnemyState::Chase:
	{
		pathFinder->SetDestination(targetPos);
		if (dis <= m_stat.atkRange)
		{
			pathFinder->Stop();
			m_state = EnemyState::CanAttack;
		}
	}
	break;
	case EnemyState::CanAttack:
	{
		m_atkTimer += fDT;
		if (m_atkTimer <= m_stat.atkDelay)
		{
			m_atkDir = dir;
			m_warnDis = dis * m_atkTimer / m_stat.atkDelay;
		}
		else if (m_warnDis > 0)
		{
			m_warnDis = 0;
			m_state = EnemyState::Attack;
		}
		if (m_atkTimer > m_stat.atkCooldown)
		{
			m_atkTimer = 0;
		}
		if (dis > m_stat.atkRange)
		{
			m_atkTimer = 0;
			m_warnDis = 0;
			m_state = EnemyState::Chase;
		}
	}
	break;
	case EnemyState::Attack:
	{
		EnemyBullet* proj = new EnemyBullet;
		proj->SetPos(m_vPos);
		proj->SetSize({ 30.f, 30.f });
		proj->SetDamage(m_stat.atkDamage);
		proj->SetDir(m_atkDir);
		proj->SetName(L"EnemyBullet");
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(proj, LAYER::PROJECTILE);
		m_state = EnemyState::CanAttack;
	}
	break;
	}
}