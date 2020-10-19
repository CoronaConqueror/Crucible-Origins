#include "BulletComponent.h"

BulletComponent::BulletComponent(Entity* o, bool dir, float ang)
{
	owner = o;
	direction = dir;

	
	angle = ang;
	
	velocity = BASEVELOCITY;

	gravity = 0;

	componentname = NAME;


	owner->AddComponent(this);
}

BulletComponent::~BulletComponent()
{
	//std::cout << "bullet destructor called" << this << std::endl;
	//owner->RemoveComponent(this);
}


void BulletComponent::Update(float deltatime)
{
	
	Vect2 coordinates = owner->GetPosition();
	//move the bullet in the velocity direction

	if (direction == 0) //left
	{
		deltax = velocity * -cos(angle);
		deltay = velocity * -sin(angle);

		//deltax = velocity;
		//deltay = gravity;

		coordinates.x += deltax * deltatime;
		coordinates.y += deltay * deltatime;

		owner->SetPosition(coordinates.x, coordinates.y);

	}
	if (direction == 1) //right
	{
		deltax = (velocity * cos(angle));
		deltay = (velocity * sin(angle));

		//deltax = velocity;
		//deltay = gravity;

		coordinates.x += deltax * deltatime;
		coordinates.y += deltay * deltatime;

		owner->SetPosition(coordinates.x, coordinates.y);
	}

	
		



	/*
	if (owner->GetPosition().x > (LEVELSIZEX / 2))
	{
		//this is to check if bullet deletion works, if at more than half screen delete the bullet
		owner->SetState(Entity::State(1)); //1 is state for dead

	}
	*/


	if (owner->GetPosition().x > (LEVELSIZEX - owner->GetComponent("SPRITE")->GetTextureSize().x)) //right level border
	{
		owner->SetState(Entity::State(1));
	}
	else if (owner->GetPosition().x < 0) //left level border
	{
		owner->SetState(Entity::State(1));
	}
	else if (owner->GetPosition().y < 0) //top level border
	{
		owner->SetState(Entity::State(1));
	}
	else if (owner->GetPosition().y > (LEVELSIZEY - owner->GetComponent("SPRITE")->GetTextureSize().y)) //bottom level border
	{
		owner->SetState(Entity::State(1));
	}
	else
	{
		//didnt hit level border
	}



}