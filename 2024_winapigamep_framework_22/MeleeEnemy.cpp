#include "pch.h"
#include "MeleeEnemy.h"
#include "Collider.h"
#include "TimeManager.h"
#include "WaveManager.h"
#include "AStarPathFinder.h"
#include "GDISelector.h"

MeleeEnemy::MeleeEnemy()
{
	m_stat.hp = 5;
	m_stat.moveSpeed = 100.f;
	m_stat.atkRange = 50.f;
	m_stat.atkCooldown = 1.f;
	m_stat.atkDamage = 5;
	m_vSize = { 30, 30 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);
}

MeleeEnemy::~MeleeEnemy()
{
	GET_SINGLE(WaveManager)->Push(ENEMY_TYPE::MELEE, new MeleeEnemy);
}

void MeleeEnemy::Update()
{
	UpdateState();
}

void MeleeEnemy::Render(HDC _hdc)
{
	HPEN newPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(_hdc, newPen);
	GDISelector brush = { _hdc, BRUSH_TYPE::HOLLOW };
	RECT_RENDER(_hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
	DeleteObject(newPen);
	SelectObject(_hdc, oldPen);
}

void MeleeEnemy::UpdateState()
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
