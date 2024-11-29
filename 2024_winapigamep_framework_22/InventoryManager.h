#pragma once
class Cell;
class Battery;
class InventoryManager
{
	DECLARE_SINGLE(InventoryManager);
private:
	~InventoryManager();
private:
	void Show();
	void Hide();
	void TryInteract(Vec2 _mousePos);
public:
	void Init();
	void Update();
	void Render(HDC _hdc);
	void ToggleInventory();
private:
	bool m_activeSelf = false;
	int m_InventorySize = SCREEN_WIDTH;
	vector<Battery*> m_vecBatteries;
	Vec2 m_curCell {};
	Battery* m_curBattery = nullptr;
	Battery* m_batteryCells[6][6] = {};
};

