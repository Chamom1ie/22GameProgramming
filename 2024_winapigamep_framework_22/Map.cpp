#include "pch.h"
#include "Map.h"
#include "GDISelector.h"
#include "AStarGrid.h"

Map::Map()
{
	m_aStarGrid = new AStarGrid;
}

Map::~Map()
{
	delete m_aStarGrid;
}

void Map::Update()
{

}

void Map::Render(HDC _hdc)
{
	GDISelector brush = { _hdc, BRUSH_TYPE::BLUE };
	RECT_RENDER(_hdc, m_vPos.x, m_vPos.y, m_vSize.x, m_vSize.y);
}
