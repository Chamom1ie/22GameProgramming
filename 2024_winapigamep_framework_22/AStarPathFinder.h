#pragma once
#include "Component.h"
class Object;
class AStarGrid;
class AStarNode;
class AStarPathFinder : public Component
{
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void SetDestination(Vec2 _pos);
	void SetAStarGrid(AStarGrid* _grid) { m_aStarGrid = _grid; }
	void Start() { m_isStopped = false; }
	void Stop() { m_isStopped = true; }
private:
	bool m_isStopped = true;
	Vec2 m_targetPos;
	AStarNode* m_targetNode = nullptr;
	AStarGrid* m_aStarGrid;
	list<Vec2> m_path;
	Vec2 m_wayPoint;
};

