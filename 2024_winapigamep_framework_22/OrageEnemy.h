#pragma once
#include "Enemy.h"
class OrageEnemy : public Enemy
{
public:
    OrageEnemy();
    ~OrageEnemy();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void UpdateState();
};

