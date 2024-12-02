#pragma once
#include "Object.h"

class AStarGrid;
class Map : public Object
{
public:
	Map();
	~Map() override;
	void Update() override;
	void Render(HDC _hdc) override;
	AStarGrid* GetAStarGrid() { return m_aStarGrid; }
private:
	AStarGrid* m_aStarGrid;
};

