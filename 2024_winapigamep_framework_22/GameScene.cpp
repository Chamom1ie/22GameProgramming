#include "pch.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "WaveManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

void GameScene::Init()
{
	{
		Object* pPlayer = new Player;
		pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
		pPlayer->SetSize({ 25.f, 25.f });
		AddObject(pPlayer, LAYER::PLAYER);
	}
	{
		Object* map = new Map;
		map->SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f });
		map->SetSize({ SCREEN_WIDTH, SCREEN_WIDTH });
		AddObject(map, LAYER::BACKGROUND);
	}
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(WaveManager)->Init();
}

void GameScene::Update()
{
	Scene::Update();
	GET_SINGLE(WaveManager)->Update();
}

void GameScene::Release()
{
	GET_SINGLE(WaveManager)->Release();
}
