#pragma once
#include "Component.h"

//this component is used to handle all "bullet" behavior for an entity
class BulletComponent : public Component
{

public:
	const std::string NAME = "BULLET";

	BulletComponent(Entity* o, bool dir, float ang);
	~BulletComponent();

	void Update(float deltatime) override;

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }


private:

	Entity* owner;

	//holds the gravity variable
	float gravity;

	//holds the velocity in the x direction
	float velocity;


	float deltax;
	float deltay;

	// 0 = left, 1 = right
	bool direction;

	std::string componentname;

	//holds the angle in radians of the bullet
	float angle;
	
};