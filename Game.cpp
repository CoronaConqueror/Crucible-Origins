#include "Game.h"
#include "Entity.h"
#include "SDL.h"
#include "SDL_image.h"
#include <algorithm>

#include "SpriteComponent.h"
#include <vector>
#include "InputComponent.h"
#include "MovementComponent.h"
#include "TurretComponent.h"
#include "CollisionComponent.h"
#include "EnemyAIComponent.h"
#include "Spawner.h"
//#include "QuadTree.h"



Game::Game()
	:window(nullptr)
	, renderer(nullptr)
	, isRunning(true)
	,idCounter(0)
	//other bools
{
	currentLevel = 0;
	NeedToLoadLevel = 1; //need to load the main menu, or the level builder as default
	spawncooldown = 1.0f;
	numPlatform = 0;
	SDL_Rect LevelBoundaries = { 0,0, LEVELSIZEX,LEVELSIZEY };

	CollisionCooldown = (3/4);
	CheckCollGrid = 1;
	//CollisionTree = new QuadTree(0, LevelBoundaries);
	xnum = 2;
	ynum = 2;
	
	

	GridEntities.reserve(xnum * ynum);

	



	

	

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Crucible Origins", 50, 50, SCREENSIZEX, SCREENSIZEY, 0);
	if (!window)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer: &s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to intialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	ticksCount = SDL_GetTicks();
	return true;


}



void Game::RunLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	int mousex; int mousey;
	SDL_Event event;
	
	


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEMOTION:
			 //save mouse position
			break;
		}
	}

	
	//SDL_GetMouseState(&mousex, &mousey);


	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	
	



	

}


void Game::UpdateGame()
{
	//compute delta time ticks count + 16
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
	{ //enforce 60 fps
	}
		
	// /1000.0f
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		ticksCount = SDL_GetTicks();

		/*
		                               // Update all actors
		
		If level needs to be loaded, do it here
		need to load all entities, like background, player, etc... based on level that needs to be loaded

			



		*/
		
		std::cout << deltaTime << "   " << entities.size() << std::endl;

		if (NeedToLoadLevel == 1) //need to load a level
		{
			//delete all entites first
			ClearScreen();



			//check which level needs to be loaded somehow and load it. for now, loads level builder as default
			LoadLevel(currentLevel);

			NeedToLoadLevel = 0; //set loadlevel bool to 0;
		}

		/* QUAD TREE ATTEMPT IT DIDNT WORK
		CollisionTree->clear(); //reset tree
		if (!entities.empty()) //if there are entities, add them in
		{

			for (auto ent : entities)
			{
				CollisionTree->insert(ent);
			}
		}



			Implement grid system HERE , cut the level up into squares and 
			find which entities are contained in each square
			when a square detects an entity within in, then add it to that square's vector
			an entity can have more than one square that it belongs to, like platforms
			then only check collision for a square that has more than one entity in it.


		*/



		/*
		
		
		for (auto vect : GridEntities[64])
		{
			if (vect.size() > 1) //there are at least two entities to check in this grid's vector
			{
				int i = 0;
				while (i < vect.size() - 1)
				{
					for (int j = i + 1; j < vect.size(); j++)
					{
						CheckCollisions(vect[i], vect[j]);
					}
					i++;
				}
				
			

			}
		}
		
		
		
		*/
		
		if (CollisionCooldown > 0.0f && CheckCollGrid == false)
		{
			CollisionCooldown -= (1 / 60);
		}
		else
		{
			CollisionCooldown = (3/4);
			CheckCollGrid = true;
		}

		if (CheckCollGrid == true)
		{
			CalculateCollisions();
			CheckCollGrid = false;
		//std::cout << CheckCollGrid << std::endl;
		}
		





		for (auto spawn : activeSpawners)
		{
			spawn->SpawnNextEntity();
		}
		
		

		updatingEntities = true;
		for (auto entity : entities)
		{
			if (&entity == nullptr)
			{
				RemoveEntity(entity);
			}
			else
			{
				//std::cout << entities.size() << std::endl;
				entity->Update(deltaTime);

				

			}
			
		}


		
		updatingEntities = false;

		for (auto pending : pendingEntities)
		{
			entities.emplace_back(pending);
		}
		pendingEntities.clear();

		

		for (auto entity : entities)
		{
			if (entity->GetState() == entity->Dead )
			{
				RemoveEntity(entity);
				
			}
		}

		//for (auto entity : deadEntities)
		//{
		//	RemoveEntity(entity);
		//}

		

		//std::cout << "deltatime = " << deltaTime << std::endl;





}


void Game::GenerateOutput()
{

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	                 // Draw all sprite components
	//for (auto sprite : mSprites)
	//{
	//	sprite->Draw(mRenderer);
	//}
	//

	


	//sort the entities into the right draw order
	std::sort(entities.begin(), entities.end());




	for (auto entity : entities)
	{
		//std::cout << entity->getDrawLevel() <<  " ";



		//std::cout << &sprite << std::endl;
		if (entity->HasComponent("SPRITE") == true ) //if entity has a sprite component draw it
		{
			entity->GetComponent("SPRITE")->Draw(renderer);
		}
		else
		{
			//no texture to draw
		}

		
		

		
	}

	//std::cout << std::endl;

	SDL_RenderPresent(renderer);

	



}


void Game::LoadData()
{
	/*
	
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
	
	
	
	*/

	screen = { 0,0,static_cast<int>(SCREENSIZEX),static_cast<int>(SCREENSIZEY) };



	/*
	

			ADD LEVEL SYSTEM HERE
			load level data from a file or internally
			store that data somewhere, can be accessed by level loader
			for now, make the generated default level the level builder
	
	*/
	//                                     level 1 data
	int levelnum = 1;
	Vect2 PlayerSpawn{ 500.0f, 500.0f };
	Vect2 OmniBulletSpawn{ 0.0f, 0.0f };
	float HPMult = 1.0f;
	float DamageMult = 1.0f;
	float SpeedMult = 1.0f;
	std::vector<Entity*> Initial;
	std::vector < Spawner*> spawners;

	SpriteComponent* sprite;
	SDL_Texture* texture;
	InputComponent* input;
	MovementComponent* movement;
	TurretComponent* turret;
	CollisionComponent* collision;

	Background = new Entity(this, Entity::Type::Background);
	Background->SetPosition(0.0f, 0.0f);
	sprite = new SpriteComponent(Background, LEVELSIZEX, LEVELSIZEY);
	texture = GetTexture("Assets/Background.png");
	sprite->SetTexture(texture);
	Initial.emplace_back(Background);


	Omni = new Entity(this, Entity::Type::Player);
	Omni->SetPosition(PlayerSpawn.x, PlayerSpawn.y);
	sprite = new SpriteComponent(Omni, 75.0f, 75.0f);
	texture = GetTexture("Assets/Omni.png");
	sprite->SetTexture(texture);
	input = new InputComponent(Omni);
	movement = new MovementComponent(Omni);
	turret = new TurretComponent(Omni, OmniBulletSpawn);
	collision = new CollisionComponent(Omni);
	Initial.emplace_back(Omni);

	Entity* entspawner = new Entity(this, Entity::Type::Spawner);
	entspawner->SetPosition(50.0f, 1300.0f);
	sprite = new SpriteComponent(entspawner, 50.0f, 50.0f);
	texture = GetTexture("Assets/Spawner.png");
	sprite->SetTexture(texture);
	Spawner* spawner = new Spawner(entspawner); //need to add entities into the spawner vector later
	spawners.emplace_back(spawner);
	Initial.emplace_back(entspawner);


	entspawner = new Entity(this, Entity::Type::Spawner);
	entspawner->SetPosition(1980.0f, 1300.0f);
	sprite = new SpriteComponent(entspawner, 50.0f, 50.0f);
	texture = GetTexture("Assets/Spawner.png");
	sprite->SetTexture(texture);
	spawner = new Spawner(entspawner); //need to add entities into the spawner vector later
	spawners.emplace_back(spawner);
	Initial.emplace_back(entspawner);


	Entity* Platform = new Entity(this, Entity::Type::Platform);
	Platform->SetPosition(600.0f, 1300.0f);
	sprite = new SpriteComponent(Platform, 600.0f, 60.0f);
	texture = GetTexture("Assets/Platform.png");
	sprite->SetTexture(texture);
	collision = new CollisionComponent(Platform);
	Initial.emplace_back(Platform);
	
	

	//this is all the data for level 1 for now
	Level* lev = new Level(levelnum, PlayerSpawn, HPMult, DamageMult, SpeedMult, Initial, spawners);
	levels.emplace_back(lev); //insert level 1 to the back of levels vector


	ClearScreen();

}

void Game::UnloadData()
{
	//delete entities
	for (auto ent : entities)
	{
		entities.pop_back(); //does this work???
	}

	//delete textures

	

}


SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;

	//load from file
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName.c_str());
		return nullptr;
	}

	//create texture from surface
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	if (!tex)
	{
		SDL_Log("Failed to convert surface to texture for &s", fileName.c_str());
		return nullptr;
	}

	//place the texture into a vector or something

	return tex;
}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//add entity code here
void Game::AddEntity(Entity* entity)
{
	
		entities.emplace_back(entity);

	
}


void Game::AddPendingEntity(Entity* entity)
{
	pendingEntities.emplace_back(entity);
}
//remove entity code here


bool operator==(Entity a, Entity b)
{
	{
		if (a.GetId() == b.GetId())
		{
			return true; //entity is equal
		}
		else
		{
			return false; //not the same entity
		}

	}
}

bool operator < (Entity a, Entity b)
{
	return (a.getDrawLevel() < b.getDrawLevel());
}



void Game::RemoveEntity(Entity* entity)
{
	

		//search the entity vector for the entity and then remove it...
		auto iter = entities.begin(); //iterator starts at beginning of vector

		iter = std::find(entities.begin(), entities.end(), entity); //returns the spot of the entity, or the last position in the vector (A NULL)

		if (iter == entities.end())
		{
			//the end of the vector was reached, no component to remove
			//do nothing
		
		}
		else
		{
			//component found...
			//swap the iterator and the end of the vector then delete
			


			if (entities.size() > 1)
			{

				


				//not the last entity
				std::iter_swap(iter, entities.end() - 1);

				//Entity* temp = entities.back();

				//delete temp;


				//entities.erase(iter);
				//std::cout << "removed an entity" << std::endl;

				//std::cout << entities.size() << std::endl;
				//int num = 1;

				for (auto comp : entities.back()->GetComponents())
				{
					//std::cout << "removing component " << num++ << std::endl;
					entities.back()->RemoveComponent(comp);
				}

				
				entities.pop_back(); //delete the last element in the vector
				
				//delete* iter;
				//*iter = nullptr;

				//std::cout << entities.size() << std::endl;





			}
			else
			{
				//this is the last entity

				//Entity* temp = entities.back();

				//delete temp;
				//std::cout << "removed an entity" << std::endl;
				//entities.erase(iter);


				


				for (auto comp : entities.back()->GetComponents())
				{
					entities.back()->RemoveComponent(comp);

				}

				
				
				entities.pop_back(); //delete the last element in the vector
				//delete* iter;
				
				
				//*iter = nullptr;





			}




		}



	

	



}

/*

//add sprite code
void Game::AddDrawingEntity(Entity* e)
{
	//add the componenet to the drawing vector
	drawingComponents.emplace_back(e);
}

//remove sprite code

void Game::RemoveDrawingEntity(Entity* e)
{
	//search the vector and then swap and remove it
	auto iter = drawingComponents.begin();

	std::find(drawingComponents.begin(), drawingComponents.end(), sprite);

	if (iter == drawingComponents.end())
	{
		//could not find it, do nothing

	}
	else
	{
		//found it, make sure to check if it is the last one then remove it

		if (drawingComponents.size() > 1)
		{
			//not the last one, swap then delete
			std::iter_swap(iter, drawingComponents.end() - 1);
			delete* iter;
			//std::cout << "sprite component removed " <<  *iter << std::endl;
			
			drawingComponents.pop_back();
			//std::cout << "Deleted Drawing Component " << std::endl;
			
		}
		else
		{
			//last one, just pop it
			delete* iter;
			
			drawingComponents.pop_back();
		}



	}



}



*/



//whatever
void Game::CreateBullet()
{
	//creates a bullet when a turret is fired...
	//Entity* Bullet = new Entity(this, getIdCounter());


}

void Game::LoadLevel(int levelnum)
{
	int c = 1;
	for (auto ent : levels[levelnum]->GetInitialEnts())
	{
		this->AddEntity(ent);
		//std::cout << c++ << std::endl;
	}

	for (auto spawn : levels[levelnum]->GetSpawners())
	{
		activeSpawners.emplace_back(spawn);
	}











	/*
	Background = new Entity(this, Entity::Type::Background);
	Background->SetPosition(0.0f, 0.0f);

	Omni = new Entity(this, Entity::Type::Player);
	Omni->SetPosition(400.0f, 400.0f);


	//Entity* background = new Entity(this, getIdCounter()); //is 'this' the game address???
	//background->SetPosition(0.0f, 0.0f);

	SpriteComponent* bg = new SpriteComponent(Background, LEVELSIZEX, LEVELSIZEY); //I think background is the owner of this component



	SDL_Texture* bgtex = GetTexture("Assets/Background.png");

	bg->SetTexture(bgtex);




	SpriteComponent* o = new SpriteComponent(Omni, 75.0f, 75.0f);

	bgtex = GetTexture("Assets/Omni.png");

	o->SetTexture(bgtex);
	

	InputComponent* i = new InputComponent(Omni);



	MovementComponent* m = new MovementComponent(Omni);
	

	Vect2 OmniBulletSpawn = Omni->GetPosition();
	OmniBulletSpawn.x += Omni->GetComponent("SPRITE")->GetTextureSize().x;
	OmniBulletSpawn.y += Omni->GetComponent("SPRITE")->GetTextureSize().y;
	TurretComponent* t = new TurretComponent(Omni, OmniBulletSpawn);



	CollisionComponent* c = new CollisionComponent(Omni);









	
	Entity* Platform = new Entity(this, Entity::Type::Platform);
	Platform->SetPosition(200.0f, 1100.0f);
	o = new SpriteComponent(Platform, 100.0f, 360.0f);
	bgtex = GetTexture("Assets/Platform.png");
	o->SetTexture(bgtex);

	c = new CollisionComponent(Platform);

	Platform = new Entity(this, Entity::Type::Platform);
	Platform->SetPosition(600.0f, 1300.0f);
	o = new SpriteComponent(Platform, 500.0f, 150.0f);
	bgtex = GetTexture("Assets/Platform.png");
	o->SetTexture(bgtex);

	c = new CollisionComponent(Platform);
	


	//Component* bg = new Component("Sprite", background);

	



	Entity* DummyEnemy = new Entity(this, Entity::Type::Enemy);

	DummyEnemy->SetPosition(600.0f, 600.0f);
	o = new SpriteComponent(DummyEnemy, 50.0f, 100.0f);
	bgtex = GetTexture("Assets/ROD.png");

	//can you reuse sprite components? YES


	o->SetTexture(bgtex);

	//i = new InputComponent(DummyEnemy);

	//m = new MovementComponent(DummyEnemy);

	c = new CollisionComponent(DummyEnemy);
	EnemyAIComponent* a = new EnemyAIComponent(DummyEnemy, EnemyAIComponent::EnemyType::ROD);

	*/

}

void Game::ClearScreen()
{
	if (entities.size() != 0 || pendingEntities.size() != 0) //check if there are entities to delete
	{
		if (pendingEntities.size() != 0)
		{
			for (auto ent : pendingEntities)
			{
				//entities.emplace_back(ent);
				pendingEntities.pop_back();
			}
		}
		
		if (entities.size() != 0)
		{
			for (auto ent : entities)
			{
				this->RemoveEntity(ent);
				//entities.pop_back();
			}
		}
		

		

		
	}
}





void Game::CreateGrid(int xSplits, int ySplits)
{
	//these holds the width and heigth of each grid
	//multiply this by the current value in the for loop to find the right coordinates to compare
	float xSections = LEVELSIZEX / xSplits;
	float ySections = LEVELSIZEY / ySplits;

	float TopLeftX = 0.0f;
	float TopLeftY = 0.0f;
	int i = 0;

	//this holds the actual grid square, use the intersect function to see if part of the entity is inside the square
	SDL_Rect* GridSquare = new SDL_Rect;

	for (int y = 0; y < ySplits; y++)
	{
		for (int x = 0; x < xSplits; x++)
		{
			//use these to calculate whether ANY of an entity's four corners are inside of it
			TopLeftX = x * xSections;
			TopLeftY = y * ySections;

			std::vector<Entity*> vect;

			GridEntities.emplace_back(vect);
			//GridEntities.pop_back();

			//this rectange is the current grid section
			//GridSquare = { static_cast<int>(TopLeftX), static_cast<int>(TopLeftY), static_cast<int>(xSections), static_cast<int>(ySections) };
			GridSquare->x = TopLeftX;
			GridSquare->y = TopLeftY;
			GridSquare->w = xSections;
			GridSquare->h = ySections;

			if (entities.size() != 0)
			{
				for (auto ent : entities)
				{


					if (ent->HasComponent("COLLISION") == true ) //check if this entity has a collision component
					{
						if (SDL_HasIntersection(GridSquare, ent->GetComponent("COLLISION")->getHITBOX()) == true) //if true add this entity into the entity vector for this square's section
						{

							GridEntities[i].emplace_back(ent);
							ent->SetGridNumber(i); //this number is the grid that the entity occupies
						}



					}

				}
			}

			//this is for the grid entities vector
			i++;
			//std::cout << i << std::endl;
		}



	}






}





void Game::CalculateCollisions()
{
	std::vector<Entity*> possCollisions; //this will be a list of all entities an entity may collide with this frame, send it to the collision component
	std::vector<Entity*> duplicateEntities;
	bool notADuplicate = true;

	

	//possCollisions.clear();
	//duplicateEntities.clear();

	if (GridEntities.size() > 0)
	{
		for (int i = 0; i < xnum * ynum; i++)
		{
			GridEntities[i].clear();
		}

	}


	for (auto ent : entities)
	{
		if (ent->HasComponent("COLLISION") == true)
		{
			ent->ClearCollisionsThisFrame();
			ent->ClearGridNumbers();
		}
		
	}







	CreateGrid(xnum, ynum);




	/*
	
	for (int a = 0; a < (xnum * ynum) - 1; a++)
	{
		//bool hasCopy = true;


		if (GridEntities[a].size() > 1 && GridEntities[a + 1].size() > 1) //there are at least two entities to check in this grid's vector
		{

			int i = 0;
			while (i < GridEntities[a].size() - 1 && i < GridEntities[a + 1].size() - 1)
			{
				for (int j = i + 1; j < GridEntities[a].size() && j < GridEntities[a + 1].size(); j++)
				{
					//CheckCollisions(GridEntities[a][i], GridEntities[a][j]);

					if (GridEntities[a][i] == GridEntities[a + 1][i] && GridEntities[a][j] == GridEntities[a + 1][j]) //if adjacent squares have the same collision detected
					{
						//delete the [a+1] entity pair
						//pop i out then j, cus of how vectors work
						auto iter = GridEntities[a].begin();
						iter = std::find(GridEntities[a].begin(), GridEntities[a].end(), GridEntities[a][j]);


						std::iter_swap(iter, GridEntities[a].end() - 1);
						GridEntities[a].pop_back();

						iter = std::find(GridEntities[a].begin(), GridEntities[a].end(), GridEntities[a][i]);
						std::iter_swap(iter, GridEntities[a].end() - 1);
						GridEntities[a].pop_back();

						//std::cout << "deleted a duplicate collision" << std::endl;

					}



				}
				i++;
			}



		}
	}


	
	
	
	
	*/
	







	//Create pairs of entities, if a pair has already been checked for collision don't check again this frame-

	/*
	
	for (int a = 0; a < xnum * ynum; a++)
	{
		if (GridEntities[a].size() > 1) //there are at least two entities to check in this grid's vector
		{
			int i = 0;
			while (i < GridEntities[a].size() - 1)
			{
				for (int j = i + 1; j < GridEntities[a].size(); j++)
				{
					CheckCollisions(GridEntities[a][i], GridEntities[a][j]);
				}
				i++;
			}



		}
	}


	

	*/
	

	for (auto ent : entities) //check every entity
	{
		possCollisions.clear();
		duplicateEntities.clear();

		

		//get all the grids this entity is inside of, combine those vectors into one big one, get rid of duplicates

		for (int gridnum : ent->GetGridNumbers()) //get the grids this entitiy is in
		{
			duplicateEntities.clear();

			if (GridEntities[gridnum].size() > 1)
			{

				for (auto gridentity : GridEntities[gridnum]) // every entity in this squares list does NOT check for duplicates currently
				{

					if (gridentity != ent && gridentity->GetType() != ent->GetType()) 
					{

						if (gridentity->GetType() == Entity::Type::Bullet && ent->GetType() == Entity::Type::Bullet) //this keeps framerate UP BUT player bullets of the same tyoe cannot collide...
						{

							

						}
						else
						{
							//search duplicate entities for gridentity, if its in there, don't add it, if its not add it
							auto iter = duplicateEntities.begin();

							iter = std::find(duplicateEntities.begin(), duplicateEntities.end(), gridentity);

							if (iter == duplicateEntities.end()) //made it to end, not a duplicate
							{
								notADuplicate = true;
								//std::cout << "didnt check a duplicate" << std::endl;
							}
							else
							{
								notADuplicate = false;
							}



							if (notADuplicate == true)
							{
								possCollisions.emplace_back(gridentity);
								duplicateEntities.emplace_back(gridentity);
							}
						}



					}

					



				}

			}

			



		}

		ent->SetCollisionsThisFrame(possCollisions);



	}


	
	

}