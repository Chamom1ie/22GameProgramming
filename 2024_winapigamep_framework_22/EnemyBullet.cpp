#include "pch.h"
#include "EventManager.h"
#include "EnemyBullet.h"
#include "Collider.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Render(HDC _hdc)
{
	ELLIPSE_RENDER(_hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}

void EnemyBullet::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void EnemyBullet::StayCollision(Collider* _other)
{
}

void EnemyBullet::ExitCollision(Collider* _other)
{
}
