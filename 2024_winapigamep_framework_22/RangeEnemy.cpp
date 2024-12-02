#include "pch.h"
#include "RangeEnemy.h"
#include "AStarPathFinder.h"
#include "TimeManager.h"
#include "WaveManager.h"

RangeEnemy::RangeEnemy()
{
	m_stat.hp = 3;
	m_stat.moveSpeed = 75.f;
	m_stat.atkRange = 200.f;
	m_stat.atkCooldown = 1.5f;
	m_stat.atkDamage = 5;
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
	RECT_RENDER(_hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
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