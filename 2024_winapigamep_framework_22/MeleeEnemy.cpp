#include "pch.h"
#include "MeleeEnemy.h"
#include "Collider.h"
#include "TimeManager.h"
#include "WaveManager.h"
#include "AStarPathFinder.h"
#include "GDISelector.h"
#include "Texture.h"

MeleeEnemy::MeleeEnemy()
{
}

MeleeEnemy::~MeleeEnemy()
{
}

void MeleeEnemy::Update()
{
	UpdateState();
}

void MeleeEnemy::Render(HDC _hdc)
{
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(m_vPos.x - width / 2)
		, (int)(m_vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
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
