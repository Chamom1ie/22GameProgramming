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
	int m_gage; //������ ex)12������
	int m_power; //�Ŀ� ex)������
	//66
};