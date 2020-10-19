#pragma once
#include "Game.h"

//this class is for holding all the data a level needs when it loads and operates
class Level
{
public:

	Level(int levelnum, Vect2 OmniSP, float EHpMult, float EDamageMult, float ESpeedMult, std::vector<Entity*> InitialEntities, std::vector<Spawner*> spawners)
	{
		levelNum = levelnum;
		OmniSpawnPoint = OmniSP;
		EnemyHPMult = EHpMult;
		EnemyDamageMult = EDamageMult;
		EnemySpeedMult = ESpeedMult;
		InitialLoadEntities = InitialEntities;
		Spawners = spawners;
	}
	~Level()
	{

	}

	std::vector<Entity*> GetInitialEnts() { return InitialLoadEntities; }

	std::vector<Spawner*> GetSpawners() { return Spawners; }

	float getHPMULT() { return EnemyHPMult; }
	float getDamMult() { return EnemyDamageMult; }
	float getSpeedMult() { return EnemySpeedMult; }

	float getLevelNUM() { return levelNum; }

	Vect2 getOmniSP() { return OmniSpawnPoint; }


private:
	std::vector<Entity*> InitialLoadEntities;

	std::vector<Spawner*> Spawners;

	float EnemyHPMult;
	float EnemyDamageMult;
	float EnemySpeedMult;

	int levelNum;

	Vect2 OmniSpawnPoint;



};