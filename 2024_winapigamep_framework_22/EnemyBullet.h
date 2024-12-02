#pragma once
#include "Projectile.h"
class EnemyBullet : public Projectile
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Render(HDC _hdc) override;
public:
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
};