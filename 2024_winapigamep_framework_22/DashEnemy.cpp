#include "pch.h"
#include "DashEnemy.h"
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

DashEnemy::DashEnemy()
{
	m_stat.hp = 3;
	m_stat.moveSpeed = 75.f;
	m_stat.atkRange = 300.f;
	m_stat.atkCooldown = 1.2f;
	m_stat.atkDelay = 0.2f;
	m_stat.atkDamage = 4;
	m_vSize = { 20, 20 };
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize(m_vSize);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"DashEnemy", L"Texture\\X-Slide.bmp");

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	m_enemyDC = CreateCompatibleDC(m_pTex->GetTexDC());
	m_enemyBmap = CreateCompatibleBitmap(m_enemyDC, width, height);
	::SelectObject(m_enemyDC, m_enemyBmap);
}

DashEnemy::~DashEnemy()
{
	DeleteObject(m_enemyBmap);
	DeleteDC(m_enemyDC);
}

void DashEnemy::Update()
{
	UpdateState();
}

void DashEnemy::Render(HDC _hdc)
{
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	//::PatBlt(m_enemyDC, 0, 0, width, height, WHITENESS);
	::BitBlt(m_enemyDC, 0, 0, width, height, _hdc, m_vPos.x, m_vPos.y, SRCCOPY);
	::TransparentBlt(m_enemyDC
		, 0, 0, width, height
		, m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	m_rad += fDT * PI;
	POINT points[3];
	points[0].x = m_vPos.x + (int)(-halfWidth * cos(m_rad) - -halfHeight * sin(m_rad));
	points[0].y = m_vPos.y + (int)(-halfWidth * sin(m_rad) + -halfHeight * cos(m_rad));
	points[1].x = m_vPos.x + (int)(halfWidth * cos(m_rad) - -halfHeight * sin(m_rad));
	points[1].y = m_vPos.y + (int)(halfWidth * sin(m_rad) + -halfHeight * cos(m_rad));
	points[2].x = m_vPos.x + (int)(-halfWidth * cos(m_rad) - halfHeight * sin(m_rad));
	points[2].y = m_vPos.y + (int)(-halfWidth * sin(m_rad) + halfHeight * cos(m_rad));
	::PlgBlt(_hdc, points, m_enemyDC
		, 0, 0, width, height, nullptr, 0, 0);
}

void DashEnemy::UpdateState()
{
	AStarPathFinder* pathFinder = GetComponent<AStarPathFinder>();
	Vec2 targetPos = m_target->GetPos();
	Vec2 dir = (targetPos - m_vPos).Normalize();
	float dis = (targetPos - m_vPos).Length();
	switch (m_state)
	{
	case EnemyState::Chase:
	{
		if (dis > m_stat.atkRange)
		{
			cout << "Chase" << endl;
			pathFinder->SetDestination(targetPos);
		}
		else
		{
			cout << "Chase to Atk" << endl;
			pathFinder->Stop();
			m_state = EnemyState::CanAttack;
		}
	}
	break;
	case EnemyState::CanAttack:
	{
		cout << "CanAtk" << endl;
		m_atkTimer += fDT;
		if (m_atkTimer > m_stat.atkDelay)
		{
			m_atkTimer = 0;
			m_atkDir = dir;
			m_state = EnemyState::Attack;
		}
	}
	break;
	case EnemyState::Attack:
	{
		cout << "Atk" << endl;
		m_atkTimer += fDT;
		if (m_atkTimer < 0.6f)
		{
			m_vPos += m_atkDir * fDT / 0.6f * m_stat.atkRange;
		}
		else if (m_atkTimer < 1.2f)
		{
			m_vPos -= m_atkDir * fDT / 0.6f * m_stat.atkRange;
		}
		else
		{
			m_atkTimer = -1;
			m_state = EnemyState::Chase;
		}
	}
	break;
	}
}