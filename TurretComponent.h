#pragma once
#include "Component.h"


/*
This component handles the firing, creation, and handling of bullets
THIS COMPONENT IS ONLY FOR OMNI, ENEMY AI WILL CREATE BULLETS FOR ENEMIES

*/


class TurretComponent : public Component
{
public:

	const std::string NAME = "TURRET";

	TurretComponent(Entity* o, Vect2 bspawnpoint);
	~TurretComponent();

	void Update(float deltatime) override;
	//void Draw(SDL_Renderer* ren) override {};

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }


private:

	//holds the entity pointer of the owner
	Entity* owner;
	

	//holds the 1 or many spawn points for bullets
	std::vector<Vect2> BulletSpawnPoints;

	//the base fire rate of the turret (gun)
	float BaseFireRate;

	//enum for BulletType
	enum BulletTypes {Base, Shredding, Rocket};

	//holds the bullet type for this turret
	int BulletType;

	//holds the barrel type
	enum BarrelTypes {Single, Twin, Triple, Minigun};

	//holds the barrel type for this turret
	int BarrelType;

	//holds the counter for firing
	float FireCooldown;

	//bool to store the turret cooldown
	bool AbleToFire;

	//keys pressed to check if space is down
	std::vector<int> keysPressed;

	std::string componentname;




	int counter;
	float angle;
	

};