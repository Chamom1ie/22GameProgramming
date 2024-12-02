#include "pch.h"
#include "AStarGrid.h"
#include "AStarNode.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "map.h"

AStarGrid::AStarGrid()
{
	Vec2 mapPos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	Vec2 mapSize = { SCREEN_WIDTH, SCREEN_WIDTH };
	mapPos -= { mapSize.x / 2, mapSize.y / 2 };

	Vec2 nodeSize = { mapSize.x / m_gridSize.x, mapSize.y / m_gridSize.y };
	Vec2 nodeRadius = nodeSize * 0.5f;

	for (int y = 0; y < m_gridSize.y; y++)
	for (int x = 0; x < m_gridSize.x; x++)
	{
		Vec2 nodePos = { x * nodeSize.x + nodeRadius.x, y * nodeSize.y + nodeRadius.y };
		nodePos += mapPos;
		m_grid[y][x] = new AStarNode(x, y, nodePos, true);
	}
}

AStarGrid::~AStarGrid()
{
	for (int y = 0; y < m_gridSize.y; y++)
	for (int x = 0; x < m_gridSize.x; x++)
		delete m_grid[y][x];
}

AStarNode* AStarGrid::GetNodeFromPosition(const Vec2& _pos)
{
	float percentX = _pos.x / SCREEN_WIDTH;
	float percentY = (_pos.y - (SCREEN_HEIGHT - SCREEN_WIDTH) / 2) / SCREEN_WIDTH;
	percentX = clamp(percentX, 0.f, 1.f);
	percentY = clamp(percentY, 0.f, 1.f);

	int x = round((m_gridSize.x - 1) * percentX);
	int y = round((m_gridSize.y - 1) * percentY);

	return m_grid[y][x];
}

vector<AStarNode*> AStarGrid::GetOpenList(const AStarNode& _node)
{
	vector<AStarNode*> openList;
	for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
	{
		if (i == 0 && j == 0) continue;
		int x = clamp(_node.X + i, 0, m_gridSize.x - 1);
		int y = clamp(_node.Y + j, 0, m_gridSize.y - 1);
		if (x < 0 || y < 0 || m_gridSize.x <= x || m_gridSize.y <= y) continue;
		if (m_grid[y][x]->IsWalkable)
		{
			openList.push_back(m_grid[y][x]);
		}
	}

	return openList;
}

std::list<Vec2> AStarGrid::GetPath(const Vec2& startPos, const Vec2& targetPos)
{
	AStarNode* startNode = GetNodeFromPosition(startPos);
	startNode->G = 0;
	AStarNode* targetNode = GetNodeFromPosition(targetPos);

	vector<AStarNode*> openList;
	vector<AStarNode*> closedList{ openList };
	AStarNode* currentNode = startNode;

	while (currentNode != targetNode)
	{
		for (auto neighbor : GetOpenList(*currentNode))
		{
			if (!neighbor->IsWalkable || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) continue;
			neighbor->G = currentNode->G + currentNode->GetDistanceCost(*neighbor);
			neighbor->H = neighbor->GetDistanceCost(*targetNode);
			neighbor->ParentNode = currentNode;
			if (std::find(openList.begin(), openList.end(), neighbor) == openList.end())
				openList.push_back(neighbor);
		}

		int idx = 0;
		if (openList.empty())
			return std::list<Vec2>();
		currentNode = openList.front();
		for (int i = 0; i < openList.size(); i++)
		{
			AStarNode* node = openList[i];
			if (node->F < currentNode->F || (node->F == currentNode->F && node->H < currentNode->H))
			{
				currentNode = node;
				idx = i;
			}
		}

		openList.erase(openList.begin() + idx);
		closedList.push_back(currentNode);
	}

	currentNode = targetNode;

	std::list<Vec2> path;
	while (currentNode != startNode)
	{
		path.push_back(currentNode->GetPos());
		currentNode = currentNode->ParentNode;
	}

	return path;
}