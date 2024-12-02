#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Collider.h"
#include "EventManager.h"
Projectile::Projectile()
//	: m_dir(-1.f)
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
{
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f, 20.f });
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	Vec2 vPos = GetPos();
	// 삼각함수의 단위가 2가지가 있다.
	// 라디안, 디그리
	//vPos.x += cosf(m_angle) * 500.f * fDT;
	//vPos.y += sinf(m_angle) * 500.f * fDT;

	vPos.x += m_vDir.x * 500.f * fDT;
	vPos.y += m_vDir.y * 500.f * fDT;
	SetPos(vPos);
	Vec2 vSize = GetSize();
	if (vPos.y < -vSize.y)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Projectile::Render(HDC _hdc)
{
	
}