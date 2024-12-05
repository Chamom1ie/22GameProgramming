#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
private:
	class Texture* m_pTex;
	int m_width, m_height;
};

