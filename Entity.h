#pragma once

#include <vector>

#include "Vect2.h"

#include "Game.h"
//#include "DrawEntity.h"


//I REMOVED ALL REFERENCES TO GAME >>>>>>>>
class Game;
class Component;




class Entity
{

public:

	enum State { Alive, Dead, Paused };
	enum Type {Background, Player, Bullet, Platform, Enemy, EnemyBullet, Spawner, UI};


	Entity(class Game* g, int32_t id);
	Entity(class Game* g);
	Entity(class Game* g, Type t);


	Entity(const Entity& E2); //copy constructor

	

	~Entity();

	State GetState() { return currState; }
	void SetState(State sta) { currState = sta; }



	//main update for entity, not for derivatives
	void Update(float deltaTime);

	//
	virtual void UpdateEntity(float deltaTime);

	//override this for derivates
	virtual void  UpdateComponents(float deltaTime);



	bool GetDirection() { return direction; }
	void SetDirection(bool dir) { direction = dir; }



	Vect2 GetPosition() { return position; }
	void SetPosition(float x, float y) { position.Set(x, y); }

	//add a component to this entity
	void AddComponent(Component* component);
	//remove component from this entity
	void RemoveComponent(Component* componenet);
	//create another entity through this entity
	Entity* CreateEntity(class Game* game, Entity* E);

	/*
	Component* GetComp(int ID)
	{
		if (ID < 0)
		{
			//weird id bug
			ID = 0;
		}
		
		return components[ID];
	}
	*/
	//returns the component based on the component name
	Component* GetComponent(std::string CompName);

	bool HasComponent(std::string CompName);



	std::vector<Component*> GetComponents() { return components; }


	//takes an integer, returns the component associated with that integer
	//Component* GetComponent(int ComponentID);


	int32_t GetId() { return id; }


	Game* getGame();

	
	Type GetType() { return EntityType; }

	void SetCollisionsThisFrame(std::vector<Entity*> collisions) { CollisionsThisFrame = collisions; }
	std::vector<Entity*> GetCollisionsThisFrame() { return CollisionsThisFrame; }
	void ClearCollisionsThisFrame() { CollisionsThisFrame.clear(); }


	void SetGridNumber(int gridNum) { GridNumbers.emplace_back(gridNum); }
	std::vector<int> GetGridNumbers() { return GridNumbers; }
	void ClearGridNumbers() { GridNumbers.clear(); }


	int getDrawLevel() { return DrawLevel; }


private:

	//holds the unique id of every entity >:(
	int32_t id;

	//holds the coordinates for the entity
	Vect2 position;


	class Game* game;

	//vector that holds all components for the entity
	std::vector<Component*> components;

	State currState;
	
	//last direction of entity
	bool direction;

	//bool enemy;

	Type EntityType;

	std::vector<Entity*> CollisionsThisFrame;

	std::vector<int> GridNumbers;

	//holds the draw level for this entity
	int DrawLevel;






};