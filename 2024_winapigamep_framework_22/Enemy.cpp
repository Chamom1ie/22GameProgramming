#include "pch.h"
#include "Enemy.h"
#include "Collider.h"
#include "AStarPathFinder.h"
#include "EventManager.h"

Enemy::Enemy()
{
	this->AddComponent<Collider>();
	this->GetComponent<Collider>()->SetSize({ 100, 100 });
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
		m_stat.hp -= 1;
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
