#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "WaveManager.h"
#include "Texture.h"

void TitleScene::Init()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Gambling", L"Texture\\gambling.bmp");
	int texWidth = m_pTex->GetWidth();
	int texHeight = m_pTex->GetHeight();

	m_width = SCREEN_WIDTH / 4;
	m_height = SCREEN_HEIGHT / 7;
}

void TitleScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}

void TitleScene::Render(HDC _hdc)
{
	for (int row = 0; row < SCREEN_WIDTH; row += m_width)
	for (int col = 0; col < SCREEN_HEIGHT; col += m_height)
	{
		::StretchBlt(_hdc, row, col, m_width, m_height
			, m_pTex->GetTexDC()
			, 0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(), SRCCOPY);
	}
}
