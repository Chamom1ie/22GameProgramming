#pragma once
class Battery;
class InventoryManager
{
	DECLARE_SINGLE(InventoryManager);
private:
	InventoryManager();
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
	bool m_activeSelf;
	int m_InventorySize = SCREEN_WIDTH;
	Battery* m_curBattery = nullptr;
	vector<Battery*> m_vecBatteries = {};
};

