#include "pch.h"
#include "InventoryManager.h"
#include "GDISelector.h"
#include "InputManager.h"
#include "Battery.h"

InventoryManager::InventoryManager()
{

}

InventoryManager::~InventoryManager()
{

}

void InventoryManager::Init()
{
	m_vecBatteries.clear();
	m_activeSelf = false;
}

void InventoryManager::Update()
{
	if (m_activeSelf)
	{

		if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
		{
			TryInteract(GET_MOUSEPOS);
		}
	}
}

void InventoryManager::Render(HDC _hdc)
{
	if (m_activeSelf)
	{
		RECT_RENDER(_hdc, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InventorySize, m_InventorySize);
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
	if (m_curBattery == nullptr)
	{
		for (auto bat : m_vecBatteries)
		{
			RECT rt = bat->GetRect();
			POINT mousePos = { (long)_mousePos.x, (long)_mousePos.y };
			if (PtInRect(&rt, mousePos))
			{
				m_curBattery = bat;
			}
		}
	}
	else
	{
	}
}

void InventoryManager::ToggleInventory()
{
	if (m_activeSelf) Hide();
	else Show();
}