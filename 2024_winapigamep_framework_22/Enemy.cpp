#include "pch.h"
#include "Enemy.h"
#include "AStarPathFinder.h"
#include "EventManager.h"
#include "Collider.h"
#include "Projectile.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{

}

void Enemy::EnterCollision(Collider* _other)
{
	std::cout << "Enter" << std::endl;
	Object* pOtherObj = _other->GetOwner();
	wstring str = pOtherObj->GetName();
	if (pOtherObj->GetName() == L"PlayerBullet")
	{
		Projectile* proj = dynamic_cast<Projectile*>(pOtherObj);
		float damage = proj->GetDamage();
		m_stat.hp -= (int)damage;
		if(m_stat.hp <= 0)
			GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
	std::cout << "Exit" << std::endl;
}
