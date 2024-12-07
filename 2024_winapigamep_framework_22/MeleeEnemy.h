#pragma once
#include "Enemy.h"
class MeleeEnemy : public Enemy
{
public:
	MeleeEnemy();
	virtual ~MeleeEnemy();
public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
private:
	void UpdateState();
};

