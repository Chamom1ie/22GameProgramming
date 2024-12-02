#pragma once
#include "Enemy.h"

class RangeEnemy : public Enemy
{
public:
	RangeEnemy();
	virtual ~RangeEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
};

