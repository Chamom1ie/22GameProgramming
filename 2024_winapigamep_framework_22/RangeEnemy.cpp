#include "pch.h"
#include "RangeEnemy.h"
#include "Collider.h"
#include "AStarPathFinder.h"
#include "TimeManager.h"
#include "WaveManager.h"
#include "GDISelector.h"

RangeEnemy::RangeEnemy()
{
	m_stat.hp = 3;
	m_stat.moveSpeed = 75.f;
	m_stat.atkRange = 200.f;
	m_stat.atkCooldown = 1.5f;
	m_stat.atkDamage = 5;
	m_vSize = { 20, 20 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);
}

RangeEnemy::~RangeEnemy()
{
}

void RangeEnemy::Update()
{
	UpdateState();
}

void RangeEnemy::Render(HDC _hdc)
{
	HPEN newPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(_hdc, newPen);
	GDISelector brush = { _hdc, BRUSH_TYPE::HOLLOW };
	RECT_RENDER(_hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
	DeleteObject(newPen);
	SelectObject(_hdc, oldPen);
}

void RangeEnemy::UpdateState()
{
	AStarPathFinder* pathFinder = GetComponent<AStarPathFinder>();
	Vec2 targetPos = m_target->GetPos();
	float dis = (targetPos - m_vPos).Length();
	switch (m_state)
	{
	case EnemyState::Chase:
	{
		pathFinder->SetDestination(targetPos);
		if (dis <= m_stat.atkRange)
		{
			pathFinder->Stop();
			m_state = EnemyState::Attack;
		}
	}
	break;
	case EnemyState::Attack:
	{
		m_atkTimer += fDT;
		if (m_atkTimer > m_stat.atkCooldown)
		{
			m_atkTimer = 0;
			m_target->ApplyDamage(m_stat.atkDamage);
		}
		if (dis > m_stat.atkRange)
			m_state = EnemyState::Chase;
	}
	break;
	}
}