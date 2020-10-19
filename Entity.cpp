#include "Entity.h"
#include <algorithm>



Entity::Entity(class Game* g, int32_t id)
	:position(0.0f, 0.0f)
	, game(g)
	, id(id)
{
	//std::cout << "id of bullet in entity " << this->GetId() << std::endl;
	game->AddEntity(this); //add the entity to the entities vector!!!
	currState = State(0);
	direction = 1;
	//enemy = 0;
}


Entity::Entity(class Game* g)
	:position(0.0f, 0.0f)
	, game(g)
{
	this->id = game->getIdCounter();
	game->AddPendingEntity(this);
	currState = State(0);
	direction = 1;
	//enemy = 0;
}

Entity::Entity(class Game* g, Type t)
	:position(0.0f, 0.0f)
	, game(g)
{
	this->id = game->getIdCounter();
	game->AddPendingEntity(this);
	currState = State(0);
	direction = 1;
	EntityType = t;


	switch (EntityType)
	{
	case Entity::Type::Background:
		{
			DrawLevel = 1; break;
		}
		

	case Entity::Type::Platform:
	{
		DrawLevel = 2; break;
	}

	case Entity::Type::Player:
	{
		DrawLevel = 3; break;
	}
	case Entity::Type::Enemy:
	{
		DrawLevel = 3; break;
	}
	case Entity::Type::Bullet:
	{
		DrawLevel = 4; break;
	}
	case Entity::Type::EnemyBullet:
	{
		DrawLevel = 4; break;
	} 

	case Entity::Type::Spawner:
	{
		DrawLevel = 2; break;
	}

	case Entity::Type::UI:
	{
		DrawLevel = 5; break;
	}

	default:
		DrawLevel = 2; break; //never let this happen XD

	}

	



}



Entity::~Entity() {
	std::cout << "Entity destuctor called " <<  this << std::endl;
	//game->RemoveEntity(this);
	/*
	while (components.size() != 0)
	{
		for (auto comp : components)
		{
			comp->~Component();
		}
	}
	*/
	
	

}


Entity::Entity(const Entity& E2)
{
	std::cout << "Copy Constructor called " << std::endl;
	game = E2.game;
	position = E2.position;
	id = E2.id;
	currState = E2.currState;
	direction = E2.direction;
}


void Entity::Update(float deltaTime)
{
	//this is updated every frame based on delta time
	//game->setUpdatingEntities(true);

	if (this == nullptr)
	{
		delete this;
	}
	else
	{
		//std::cout << "current entity is " << this << std::endl;
		UpdateEntity(deltaTime);
		UpdateComponents(deltaTime);
	}

		
	
	
	
	
	
	
}

void Entity::UpdateEntity(float deltaTime)
{


}

void Entity::UpdateComponents(float deltaTime)
{
	for (auto comp : components)
	{
		comp->Update(deltaTime);
	}

}

void Entity::AddComponent(Component* component)
{
	//put the new component in the back of the vector...
	components.emplace_back(component);
}

void Entity::RemoveComponent(Component* component)
{

	

	//search the components vector for the component and then remove it...
	auto iter = components.begin(); //iterator starts at beginning of vector

	iter = std::find(components.begin(), components.end(), component);

	if (iter == components.end())
	{
		//the end of the vector was reached, no component to remove
		//do nothing
	}
	else
	{
		//component found...
		//swap the iterator and the end of the vector then delete

		if (components.size() > 1)
		{
			std::iter_swap(iter, components.end() - 1);

			
			delete* iter;
			//components.pop_back(); //delete the last element in the vector
		}
		else
		{
			
			//delete* iter;
			components.pop_back();
		}

		

	}


}


Entity* Entity::CreateEntity(class Game* game, Entity* E)
{
	//use the passed entity pointer to assign a new entity to it???
	
	E = new Entity(game);
	//create a new pointer for the entity
	return E;

	//return the new entity to whatever needs it to modify it???
	
}


Game* Entity::getGame()
{
	return game;
}

/*
template <typename T>
T* Entity::GetComponent(int ID)
{
	return components[ID];
}

*/

Component* Entity::GetComponent(std::string CompName)
{
	if (components.size() != 0)
	{
		for (auto comp : components)
		{
			if (comp->GetComponentName() == CompName)
			{
				return comp;
			}
			else
			{
				//return 0;
				//do nothing
			}
		}

	}


}


bool Entity::HasComponent(std::string CompName)
{
	if (components.size() != 0)
	{
		for (auto comp : components)
		{
			if (comp->GetComponentName() == CompName)
			{
				return 1;
			}
			else
			{
				//do nothing
			}
		}
		return 0;

	}
}