#pragma once
#include "Component.h"
#include "QuadTree.h"

//this component handles all collision detection, 
class CollisionComponent : public Component
{

public:

	const std::string NAME = "COLLISION";

	CollisionComponent(Entity* o);

	~CollisionComponent();

	void Update(float deltatime) override;

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }

	Vect2 GetMidPoint() override { return MidPoint; }



	//SDL_Rect* GetHitBox() override { return HitBox; }

	//check owner against ent to show which side collided
	
	void CheckCollisions(Entity* ent);

	std::string CheckSide(SDL_Rect owner, SDL_Rect ent);

	SDL_Rect* getHITBOX() { return HitBox; }



private:
	Entity* owner;

	std::string componentname;

	//holds the midpoint for distance calculations
	Vect2 MidPoint;
	Vect2 OMidPoint;

	//holds the coordinates for this entity's hitbox
	SDL_Rect* HitBox;

	//angle of the collision
	//float angle;


	
};