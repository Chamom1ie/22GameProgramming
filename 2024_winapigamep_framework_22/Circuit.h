#pragma once
class Battery;
class Circuit
{
public:
	Circuit();
	~Circuit();
private:

private:
	vector<Battery*> m_vecBatteries;
	int m_gage; //게이지 ex)12게이지
	int m_power; //파워 ex)저격총
	//66
};