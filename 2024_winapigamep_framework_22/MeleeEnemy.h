#pragma once
#include "Enemy.h"
class MeleeEnemy : public Enemy
{
public:
	MeleeEnemy();
	virtual ~MeleeEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
};

