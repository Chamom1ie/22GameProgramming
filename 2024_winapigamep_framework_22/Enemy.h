#pragma once
#include "Object.h"

enum class EnemyState
{
	Chase,
	Attack
};

class AStarPathFinder;
class Enemy :
    public Object
{
public:
	Enemy();
	virtual ~Enemy();
public:
	void Update() abstract;
	void Render(HDC _hdc) abstract;
	void SetTarget(Object* _target) { m_target = _target; };
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	ENEMY_TYPE m_type;
protected:
	Object* m_target;
	float m_atkTimer = 0;
	EnemyState m_state;
};

