#pragma once
class Cell;
class Battery;
class Button;
class InventoryManager
{
	DECLARE_SINGLE(InventoryManager);
private:
	~InventoryManager();
private:
	void Show();
	void Hide();
	void TryInteractToSeri(Vec2 _mousePos);
	void TryInteractToPara(Vec2 _mousePos);
public:
	void Init();
	void Update();
	void Render(HDC _hdc);
	void ToggleInventory();
	int GetSeriCount() { return m_seriCount; }
	int GetParaCount() { return m_paraCount; }
private:
	bool m_activeSelf = false;
	int m_InventorySize = SCREEN_WIDTH;
	int m_seriCount = 0;
	int m_paraCount = 0;
	int m_batteryCount = 0;
	Button* m_addSeriBtn;
	Button* m_subSeriBtn;
	Button* m_addParaBtn;
	Button* m_subParaBtn;
};

