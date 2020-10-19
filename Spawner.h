#pragma once
#include "Level.h"
//this class holds the spawner entity as well as a vector of all the entities that the spawner will spawn
class Spawner
{
public:
	Spawner(Entity* o)
	{
		spawnercooldown = 5.0f;
		canSpawn = 0;
		owner = o;
	}

	~Spawner()
	{

	}

	void AddtoSpawner(Entity* ent)
	{
		SpawnEntities.emplace_back(ent);
	}

	void SpawnNextEntity()
	{
		if (SpawnEntities.size() != 0)
		{
			if (spawnercooldown > 0.0f && canSpawn == 0)
			{
				spawnercooldown -= 0.01666;
			}
			else if (spawnercooldown < 0.0f and canSpawn == 0)
			{
				spawnercooldown = 5.0f;
				canSpawn = 1;
			}

			if (canSpawn == 1)
			{
				owner->getGame()->AddEntity(SpawnEntities.back());
				SpawnEntities.pop_back();
				canSpawn = 0;
			}

			
		}
		
	}


private:
	//holds the pointer to the current game object
	//Game* game;

	//pointer of this spawner
	Entity* owner;

	//holds the entities to be spawned by this spawner
	std::vector<Entity*> SpawnEntities;
	float spawnercooldown;
	bool canSpawn;


};