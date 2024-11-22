#pragma once
#include "Object.h"
class Texture;
class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void ShowInventory();
private:
	void CreateProjectile();
	Texture* m_pTex;
	float m_atkCooldown = 0.2f;
	float timer = 0;
	bool _enable = false;
};

