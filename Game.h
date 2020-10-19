#pragma once

#include "SDL.h"
#include <vector>
#include <string>

#include "Component.h"
#include "Entity.h"

//#include "SpriteComponent.h"
class Entity;

class TurretComponent;
class SpriteComponent;
class InputComponent;
class MovementComponent;
class BulletComponent;
class CollisionComponent;
class EnemyAIComponent;
class Level;
class Spawner;
//class QuadTree;




//these are all the games constants, change them here
const float LEVELSIZEX = 2048.0f;
const float LEVELSIZEY = 1536.0f;

const float SCREENSIZEX = 1024.0f;
const float SCREENSIZEY = 768.0f;

const float BASEVELOCITY = 575.0f;
const float BASEGRAVITY = 20.0f;

const float MAXRIGHTBULLVEL = 7.0f;
const float MAXLEFTBULLVEL = -7.0f;

const float MAXOMNIVEL = 7.0f;
const float OMNIACCELERATION = 10.0f;
const float OMNIJUMP = 15.0f;
const float TERMINALVEL = 20.0f;

const float FRICTION = 5.5f;


const float BASEENEMYVEL = 10.0f;
const float MAXENEMYVEL = 6.0f;

/*

struct DrawEntity
{
	Entity* owner;
	int drawlevel;

	DrawEntity(Entity* own, int drawlvl) { owner = own; drawlevel = drawlvl; }

	bool operator < (const DrawEntity& Ent1)
	{
		return (drawlevel < Ent1.drawlevel);
	}

	bool operator == (const Entity* Ent1)
	{
		return (owner == Ent1);
	}
};



*/




class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	//add an entity to the entities vector
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetEntities() { return entities; }

	//add an entity to the pending entities
	void AddPendingEntity(Entity* entity);

	//remove an entity from the entities vector
	void RemoveEntity(Entity* entity);

	int32_t getIdCounter() { return ++idCounter; }

	int32_t showID() { return idCounter; }


	friend bool operator==(Entity a, Entity b);
	

	void setUpdatingEntities(bool state) { updatingEntities = state; }




	SDL_Texture* GetTexture(const std::string& fileName);


	//add to drawingComponents
	//void AddDrawingEntity(Entity* e);

	//remove from drawing components
	//void RemoveDrawingEntity(Entity* e);


	//create a bullet entity
	void CreateBullet();

	//return the screen components as a sdl rectangle
	SDL_Rect GetScreen() { return screen; }
	void SetScreen(SDL_Rect s) { screen = s; }

	//boundaries
	bool GetRightBound() { return RightBound; }
	void SetRightBound(bool r) { RightBound = r; }

	bool GetBottomBound() { return BottomBound; }
	void SetBottomBound(bool b) { BottomBound = b; }

	Entity* GetOmni() { return Omni; } //returns the pointer for the player, Omni

	//deletes all entities on screen
	void ClearScreen();

	//choose which level you need to bu
	void LoadLevel(int lvlnum);

	//this funtion takes the x and y splits of the grid you want to make of the level,
	//it then creates vectors of entity pointers that will be populated by checking if ONLY ONE CORNER OF AN ENTITY's HITBOX IS IN THAT SECTION
	//DONT ADD AN ENTITY INTO A GRID's VECTOR MORE THAN ONCE
	//aftwards every square of the grid then runs CheckCollisions for every pair of entities in its vector
	//to be eligible to check, the square has to have more than one entity in it

	void CreateGrid(int xSplits, int ySplits);


	//this function taking in two entities, checks if they intersect, then does actions to the left entity (the owner)
	//void CheckCollisions(Entity* owner, Entity* ent);
	//std::string CheckSide(SDL_Rect owner, SDL_Rect ent);

	//QuadTree* getCollTree() { return CollisionTree; }


	void CalculateCollisions();


	//std::vector<DrawEntity> getDrawSprites() { return DrawSprites; };

private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	SDL_Window* window;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;

	//bool updatingActors
	bool updatingEntities;

	//entity pointers here
	std::vector<Entity*> entities;
	std::vector<Entity*> drawingEntities;
	std::vector<Entity*> pendingEntities;

	//holds all the sprites that needs drawing ------ static images for now
	//std::vector<class SpriteComponent*> drawingComponents;

	//holds the counter for entity creation
	//add 1 every time an entity is created for tracking
	int32_t idCounter;

	//vector of all textures
	//std::vector<SDL_Texture*> allTexture;


	//area for all of the game specific pointers
	Entity* Omni;
	Entity* Background;

	//rect for the screen
	SDL_Rect screen;

	//bool to check screen boundaries
	bool BottomBound;
	bool RightBound;

	//bool to hold whether the game needs to load a level or not
	//a level can be main menu, level builder, or the actual levels
	bool NeedToLoadLevel;
	int currentLevel;

	bool inMainMenu;

	float spawncooldown;
	int numPlatform;


	std::vector<Level*> levels;
	std::vector<Spawner*> activeSpawners;


	//std::vector<Entity*> possiblecoll;

	//QuadTree* CollisionTree;
	int xnum;
	int ynum;
	//vector of Entity vectors for the grid tiles
	std::vector<std::vector<Entity*>> GridEntities;
	//std::array<std::vector<Entity*>, 64> GridEntities;

	float CollisionCooldown;
	bool CheckCollGrid;

	//std::vector<DrawEntity> DrawSprites;

};


