#pragma once

class AStarNode;
class AStarGrid
{
public:
	AStarGrid();
	~AStarGrid();
	AStarNode* GetNodeFromPosition(const Vec2& _pos);
	std::list<Vec2> GetPath(const Vec2& startPos, const Vec2& targetPos);
private:
	vector<AStarNode*> GetOpenList(const AStarNode& _node);
	AStarNode* m_grid[100][100];
	Vec2Int m_gridSize = { 100, 100 };
};