#pragma once
#include "Object.h"
class Texture;
class Projectile : public Object
{
public:
	Projectile();
	virtual ~Projectile();
	void Update() override;
	virtual void Render(HDC _hdc) override;
public:
	void SetAngle(float _f)
	{
		m_angle = _f;
	}
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
	void SetDamage(float _damage)
	{
		m_damage = _damage;
	}
	float GetDamage() { return m_damage; }
public:
	virtual void EnterCollision(Collider* _other) = 0;
	virtual void StayCollision(Collider* _other) = 0;
	virtual void ExitCollision(Collider* _other) = 0;
private:
	//float m_dir;
	float m_angle;
	float m_damage;
	Vec2 m_vDir;
};

