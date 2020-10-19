#pragma once
#include "Component.h"


//this component uses the input component to determine how the entity moves,
//if there is not input, then use the AI component for movement!!!

//THIS COMPONENT IS FOR THE PLAYER ONLY

class MovementComponent : public Component
{
public:

	const std::string NAME = "MOVEMENT";

	MovementComponent(Entity* o);
	~MovementComponent();

	void Update(float deltatime) override;

	//void SetState(int s) { state = s; }
	//int GetState() { return state; }

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }

	float getDeltaX() { return deltax; }
	float getDeltaY() { return deltay; }

	void SetDeltaX(float dx) override { deltax = dx; }
	void SetDeltaY(float dy) override { deltay = dy; }
	void SetJumping(bool b) override { Jumping = b; }
	float GetDeltaY() override { return deltay; }
	float GetDeltaX() override { return deltax; }
	float GetAngle() override { return angle; }



private:

	//holds the pointer to the owning entity, to modify it
	Entity* owner;

	//these floats are the vectors that will move the entity
	float deltax;
	float deltay;

	//copy the input vector of keys into this vector to use for movement
	std::vector<int> kPressed;

	//0 - not jumping, 1 - jumping
	//enum State {NotJumping, Jumping, Moving, NotMoving};
	//int state;

	bool Jumping;
	bool Moving;

	SDL_Rect screenCopy;

	std::string componentname;
	//angle of the velocity of omni
	float angle;


};