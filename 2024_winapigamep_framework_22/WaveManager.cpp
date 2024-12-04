#include "pch.h"
#include "WaveManager.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"
#include "DashEnemy.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Map.h"
#include "AStarPathFinder.h"

void WaveManager::Init()
{
    m_mt.seed(m_rd());

    for (int i = 0; i < 10; i++)
    {
        Enemy* enemy = new MeleeEnemy;
        m_enemyTable[(int)ENEMY_TYPE::MELEE].push(enemy);
    }
    for (int i = 0; i < 10; i++)
    {
        Enemy* enemy = new RangeEnemy;
        m_enemyTable[(int)ENEMY_TYPE::RANGE].push(enemy);
    }
    for (int i = 0; i < 10; i++)
    {
        Enemy* enemy = new DashEnemy;
        m_enemyTable[(int)ENEMY_TYPE::DASH].push(enemy);
    }

    m_waves[1] = { 1, { /*ENEMY_TYPE::MELEE, ENEMY_TYPE::RANGE, */ENEMY_TYPE::DASH}, 1};

    m_player = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
    Object* obj = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::BACKGROUND)[0];
    m_map = dynamic_cast<Map*>(obj);
}

void WaveManager::Update()
{
    SpawnWave();
}

void WaveManager::Release()
{
    for (int i = 0; i < (int)ENEMY_TYPE::END; i++)
    {
        while (m_enemyTable[i].size())
        {
            if (m_enemyTable[i].top() != nullptr)
                delete m_enemyTable[i].top();
            m_enemyTable[i].pop();
        }
    }
}

bool WaveManager::IsWaveEnd()
{

    return false;
}

void WaveManager::SpawnWave()
{
    m_currentTime += fDT;
    Wave wave = m_waves[m_currentWave];
    if (m_currentTime > m_spawnIntv
        && m_remainEnemyCnt < wave.spawnCnt)
    {
        m_currentTime = 0;
        std::uniform_int_distribution<int> typeIdx(0, wave.enemyTypeCnt - 1);
        ENEMY_TYPE type = wave.spawnEnemies[typeIdx(m_mt)];
        Enemy* enemy = m_enemyTable[(int)type].top();
        enemy->SetPos({ 150 * m_remainEnemyCnt, 300 });
        enemy->SetName(L"Enemy");
        enemy->SetTarget(m_player);
        enemy->AddComponent<AStarPathFinder>();
        enemy->GetComponent<AStarPathFinder>()->SetAStarGrid(m_map->GetAStarGrid());

        GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(enemy, LAYER::ENEMY);
        m_enemyTable[(int)type].pop();
        m_remainEnemyCnt++;
    }
}