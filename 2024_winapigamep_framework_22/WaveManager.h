#pragma once

class Object;
class Enemy;
class Map;
struct Wave
{
	int spawnCnt;
	ENEMY_TYPE spawnEnemies[(int)ENEMY_TYPE::END];
	int enemyTypeCnt;
};

class WaveManager
{
	DECLARE_SINGLE(WaveManager)
public:
	void Init();
	void Update();
	void Release();
	bool IsWaveEnd();
	void Push(ENEMY_TYPE type, Enemy* enemy) { m_enemyTable[(int)type].push(enemy); }
	void SpawnEnemy(ENEMY_TYPE types[], int cnt = 3);
private:
	void SpawnWave();
	Vec2 GetRandomPosition();
private:
	Wave m_waves[25];
	int m_currentWave = 1;
	float m_spawnIntv = 1.f;
	float m_currentTime = 1;
	int m_remainEnemyCnt = 0;
	std::stack<Enemy*> m_enemyTable[(int)ENEMY_TYPE::END];
	Object* m_player;
	Map* m_map;

	std::random_device m_rd;
	std::mt19937 m_mt;
};

