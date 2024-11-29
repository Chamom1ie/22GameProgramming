#include "pch.h"
#include "InventoryManager.h"
#include "GDISelector.h"
#include "InputManager.h"
#include "Battery.h"
#include "Texture.h"

InventoryManager::~InventoryManager()
{

}

void InventoryManager::Init()
{
	m_activeSelf = false;
	m_vecBatteries.clear();
}

void InventoryManager::Update()
{
	if (m_activeSelf)
	{

		#pragma region Test

		if (GET_KEYDOWN(KEY_TYPE::H))
		{
			Battery* btr = new Battery;
			int btrCnt = m_vecBatteries.size();
			if (btrCnt >= 5) return;
			m_vecBatteries.push_back(btr);
			cout << m_vecBatteries.size();
		}

		#pragma endregion

		if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
		{
			TryInteract(GET_MOUSEPOS);
			if (m_curBattery != nullptr && 
				m_curCell != Vec2(0, 0) && 
				m_batteryCells[(int)m_curCell.x][(int)m_curCell.y] == nullptr)
			{
				m_batteryCells[(int)m_curCell.x][(int)m_curCell.y] = m_curBattery;
				m_curBattery = nullptr;
			}
		}
	}
}

void InventoryManager::Render(HDC _hdc)
{
	if (m_activeSelf)
	{
		Vec2 inventoryPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		RECT_RENDER(_hdc, inventoryPos.x, inventoryPos.y, m_InventorySize, m_InventorySize);

		Vec2 coreSize = { 50,50 };
		Vec2 corePos = { (int)((coreSize.x / 2) + (coreSize.x / 4)), SCREEN_HEIGHT / 2 };
		ELLIPSE_RENDER(_hdc, corePos.x, corePos.y, 50, 50);

		Vec2 gunSize = { 50,50 };
		Vec2 gunPos = { (int)(SCREEN_WIDTH - (gunSize.x / 2) - (gunSize.x / 4)), SCREEN_HEIGHT / 2 };
		RECT_RENDER(_hdc, gunPos.x, gunPos.y, gunSize.x, gunSize.y);


		int originY = SCREEN_HEIGHT / 2 - m_InventorySize / 2;
		int padding = 5;

		Vec2 btrSize = { 90,60 };
		Vec2 btrPos =
		{
			(int)(50 + btrSize.x / 2),
			(int)(originY + btrSize.y / 2)
		};
		btrPos.x += 25.f;
		btrPos.y += ((btrSize.y + padding) * 2.5f) + padding;
		for (int y = 0; y < 6; ++y)
		for (int x = 0; x < 6; ++x)
		{
			RECT_RENDER(_hdc, 
				btrPos.x + (btrSize.x + padding) * x, 
				btrPos.y + (btrSize.y + padding) * y, 
				btrSize.x, 
				btrSize.y);
			if (m_batteryCells[x][y] != nullptr)
			{
				GDISelector selector(_hdc, BRUSH_TYPE::YELLOW);
				RECT_RENDER(_hdc,
					btrPos.x + (btrSize.x + padding) * x,
					btrPos.y + (btrSize.y + padding) * y,
					btrSize.x,
					btrSize.y);
				m_batteryCells[x][y]->SetPos(btrPos);
				m_batteryCells[x][y]->SetSize(btrSize);
			}
		}

		int formalBtrSizeX = 140;
		int formalBtrSizey = 90;
		int formalBtrX = formalBtrSizeX / 2;
		int formalBtrY = (SCREEN_HEIGHT / 2) + (m_InventorySize / 2) - (formalBtrSizey / 2) - padding;

		for (int i = 0; i < 5; i++)
		{
			int cnt = m_vecBatteries.size();
			if (cnt <= i) continue;
			if (m_vecBatteries[i] != nullptr)
			{
				m_vecBatteries[i]->SetPos(Vec2(formalBtrX, formalBtrY));
				m_vecBatteries[i]->SetSize(Vec2(formalBtrSizeX,formalBtrSizey));

				GDISelector selector(_hdc, BRUSH_TYPE::YELLOW);
				RECT_RENDER(_hdc, formalBtrX, formalBtrY, formalBtrSizeX, formalBtrSizey);
				formalBtrX += formalBtrSizeX + padding;
			}
		}

		if (m_curBattery != nullptr)
		{
			Vec2 mousePos = GET_MOUSEPOS;
			RECT_RENDER(_hdc, mousePos.x, mousePos.y, btrSize.x, btrSize.y);
		}
	}
}

void InventoryManager::Show()
{
	m_activeSelf = true;
}

void InventoryManager::Hide()
{
	m_activeSelf = false;
}

void InventoryManager::TryInteract(Vec2 _mousePos)
{
	POINT mousePos = { (long)_mousePos.x, (long)_mousePos.y };
	if (m_curBattery != nullptr)
	{
		for (int y = 0; y < 6; ++y)
		for (int x = 0; x < 6; ++x)
		{
			if (m_batteryCells[x][y] == nullptr) continue;

			cout << "에엥";

			RECT rt = m_batteryCells[x][y]->GetRect();
			POINT mousePos = { (long)_mousePos.x, (long)_mousePos.y };

			if (PtInRect(&rt, mousePos))
			{
				cout << "그니까 이게되니까 지금 이러지";
				m_curCell = { x,y };
			}
		}
	}
	else
	{
		for (int y = 0; y < 6; ++y)
		for (int x = 0; x < 6; ++x)
		{
			if (m_batteryCells[x][y] == nullptr) continue;
			RECT rt = m_batteryCells[x][y]->GetRect();
			if (PtInRect(&rt, mousePos))
			{
				m_curBattery = m_batteryCells[x][y];
			}
		}

		for (auto btr : m_vecBatteries)
		{
			if (btr == nullptr) continue;

			RECT rt = btr->GetRect();
			if (PtInRect(&rt, mousePos))
			{
				m_curBattery = btr;
				m_vecBatteries.pop_back();
			}
		}
	}
}

void InventoryManager::ToggleInventory()
{
	if (m_activeSelf) Hide();
	else Show();
}