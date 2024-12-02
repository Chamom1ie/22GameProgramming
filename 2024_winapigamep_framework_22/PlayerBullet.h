#pragma once
#include "Projectile.h"

class Texture;
class PlayerBullet : public Projectile
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Render(HDC _hdc) override;
public:
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
	Texture* m_pTex;
};

