#pragma once
#include "Component.h"

/*
	This component handles the movement and behavior of enemies
	Use an enum type to differentiate between ai behaviors
	EX: Type ROD = follow player and try to collide with him
		Type FROD = hover to player up to a certain distance then shoot a bullet

		include deltax and deltay components for moving and collision
*/
class EnemyAIComponent : public Component
{
public:
	enum EnemyType { ROD, FROD, GROD };

	EnemyAIComponent(Entity* o, EnemyType t);
	~EnemyAIComponent();

	void Update(float deltatime) override;

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }


	
	const std::string NAME = "ENEMYAI";


private:
	Entity* owner;
	std::string componentname;

	//these floats are the vectors that will move the entity
	float deltax;
	float deltay;
	float velocity; //for movement speed 
	float movementtimer; //a timer for deciding when to move, cooldown
	bool canMove;
	


	bool Jumping;
	bool Moving;

	float angle;

	//holds the type of the enemy for ai decisions
	EnemyType type;



};

