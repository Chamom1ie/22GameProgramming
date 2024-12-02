#include "pch.h"
#include "InventoryManager.h"
#include "GDISelector.h"
#include "InputManager.h"
#include "Battery.h"
#include "Texture.h"
#include "Button.h"

InventoryManager::~InventoryManager()
{

}

void InventoryManager::Init()
{
	Vec2 btnSize = Vec2(120, 60);
	Vec2 btnPos = { (int)SCREEN_WIDTH / 5, ((int)((SCREEN_HEIGHT - m_InventorySize / 2) + btnSize.y)) };
	btnPos.x -= SCREEN_WIDTH / 64;

	m_addSeriBtn = new Button(btnSize, btnPos);
	btnPos.x += SCREEN_WIDTH / 8 + btnSize.x /2;
	m_subSeriBtn = new Button(btnSize, btnPos);
	btnPos.x += SCREEN_WIDTH / 8 + btnSize.x / 2;
	m_addParaBtn = new Button(btnSize, btnPos);
	btnPos.x += SCREEN_WIDTH / 8 + btnSize.x / 2;
	m_subParaBtn = new Button(btnSize, btnPos);
	m_activeSelf = false;
	m_seriCount = 1;
	m_paraCount = 1;
}

void InventoryManager::Update()
{
	if (m_activeSelf)
	{

		#pragma region Test

		if (GET_KEYDOWN(KEY_TYPE::H))
		{
			m_batteryCount++;
		}

		#pragma endregion

		if (GET_KEYDOWN(KEY_TYPE::LBUTTON))
		{
			TryInteractToSeri(GET_MOUSEPOS);
			TryInteractToPara(GET_MOUSEPOS);
		}
	}
}

void InventoryManager::Render(HDC _hdc)
{
	if (m_activeSelf)
	{
		Vec2 inventoryPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		RECT_RENDER(_hdc, inventoryPos.x, inventoryPos.y, m_InventorySize, m_InventorySize);

		RECT_RENDER(_hdc, m_addSeriBtn->GetPos().x, m_addSeriBtn->GetPos().y, m_addSeriBtn->GetSize().x, m_addSeriBtn->GetSize().y);
		RECT_RENDER(_hdc, m_subSeriBtn->GetPos().x, m_subSeriBtn->GetPos().y, m_subSeriBtn->GetSize().x, m_subSeriBtn->GetSize().y);
		RECT_RENDER(_hdc, m_addParaBtn->GetPos().x, m_addParaBtn->GetPos().y, m_addParaBtn->GetSize().x, m_addParaBtn->GetSize().y);
		RECT_RENDER(_hdc, m_subParaBtn->GetPos().x, m_subParaBtn->GetPos().y, m_subParaBtn->GetSize().x, m_subParaBtn->GetSize().y);

		Vec2 btrCountSize = { 150 , 100 };
		int padding = 75;
		Vec2 btrCountPos = { SCREEN_WIDTH / 2 - btrCountSize.x / 2 - padding, SCREEN_HEIGHT / 2 - m_InventorySize / 2 + btrCountSize.y / 2 + padding };

		std::wstring seriStr = std::to_wstring(m_seriCount);
		RECT_RENDER(_hdc, btrCountPos.x, btrCountPos.y, btrCountSize.x, btrCountSize.y);
		TextOut(_hdc, btrCountPos.x, (btrCountPos.y + btrCountSize.y / 2 + btrCountSize.y / 4), seriStr.c_str(), seriStr.length());

		std::wstring paraStr = std::to_wstring(m_paraCount);
		btrCountPos = { SCREEN_WIDTH / 2 + btrCountSize.x / 2 + padding, SCREEN_HEIGHT / 2 - m_InventorySize / 2 + btrCountSize.y / 2 + padding };
		RECT_RENDER(_hdc, btrCountPos.x, btrCountPos.y, btrCountSize.x, btrCountSize.y);
		TextOut(_hdc, btrCountPos.x, (btrCountPos.y + btrCountSize.y / 2 + btrCountSize.y / 4), paraStr.c_str(), paraStr.length());

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

void InventoryManager::TryInteractToSeri(Vec2 _mousePos)
{
	POINT mousePos = { (long)_mousePos.x, (long)_mousePos.y };

	RECT addRt = m_addSeriBtn->GetRect();
	RECT subRt = m_subSeriBtn->GetRect();
	if (PtInRect(&addRt, mousePos))
	{
		if (m_seriCount >= 50) return;
		m_batteryCount--;
		m_seriCount++;
	}

	if (PtInRect(&subRt, mousePos))
	{
		if (m_seriCount <= 1) return;
		m_batteryCount++;
		m_seriCount--;
	}
}

void InventoryManager::TryInteractToPara(Vec2 _mousePos)
{
	POINT mousePos = { (long)_mousePos.x, (long)_mousePos.y };

	RECT addRt = m_addParaBtn->GetRect();
	RECT subRt = m_subParaBtn->GetRect();

	if (PtInRect(&addRt, mousePos))
	{
		if (m_paraCount >= 10) return;
		m_batteryCount--;
		m_paraCount++;
	}

	if (PtInRect(&subRt, mousePos))
	{
		if (m_paraCount <= 1) return;
		m_batteryCount++;
		m_paraCount--;
	}
}

void InventoryManager::ToggleInventory()
{
	if (m_activeSelf) Hide();
	else Show();
}