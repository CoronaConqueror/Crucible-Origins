#include "TurretComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"

TurretComponent::TurretComponent(Entity* o, Vect2 bspawnpoint)
{
	owner = o;

	BarrelType = Single; //base

	BulletType = Base; //base

	BaseFireRate = 0.025f; //base

	AbleToFire = 0; //is not able to fire

	FireCooldown = BaseFireRate; //1 second cooldown

	BulletSpawnPoints.emplace_back(bspawnpoint); //sets the bullet spawn coordinate

	owner->AddComponent(this); //add this component(turret component) to owner's component vector

}

TurretComponent::~TurretComponent()
{
	//owner->RemoveComponent(this);
}


void TurretComponent::Update(float deltatime)
{

	Entity* Bullet = nullptr;
	//check if the owner is currently firing this frame
	//check if the turret is not on cooldown (firerate)
	Vect2 coor = owner->GetPosition();
	
	coor.x += (owner->GetComponent("SPRITE")->GetTextureSize().x / 2) - 5; //the 5 is from bullet type
	coor.y += (owner->GetComponent("SPRITE")->GetTextureSize().y / 2) - 5;
	
	BulletSpawnPoints[0].x = coor.x;
	BulletSpawnPoints[0].y = coor.y;

	

	SpriteComponent* sprite;
	BulletComponent* bullcomp;
	SDL_Texture* tex;
	CollisionComponent* coll;
	
	




	if (FireCooldown > 0.0f && AbleToFire == 0) //if not able to fire
	{
		
		//reduce it by one "tick" 1/60th of a second
		FireCooldown = FireCooldown - 0.016f;
		//std::cout << FireCooldown << std::endl;

	}
	else
	{
		AbleToFire = 1; //ready to fire
		FireCooldown = BaseFireRate; //reset the cooldown
	}


	keysPressed = owner->GetComponent("INPUT")->GetKeys();

	while (!keysPressed.empty())
	{
		int temp = 0;
		temp = keysPressed.back();

		if (temp == SDL_SCANCODE_SPACE) //A key pressed
		{
			//check if on cooldown
			if (AbleToFire == 1)
			{
				//fire a bullet
				

				//apply a new pointer to the bullet entity
				//Bullet = new Entity(owner->getGame(), owner->getGame()->getIdCounter());
				//Bullet = owner->CreateEntity(owner->getGame(), Bullet);
				Bullet = new Entity(owner->getGame(), Entity::Type::Bullet);

				Bullet->SetPosition(BulletSpawnPoints[0].x, BulletSpawnPoints[0].y);

				sprite = new SpriteComponent(Bullet, 10.0f, 10.0f);
				tex = owner->getGame()->GetTexture("Assets/OmniBaseBullet.png");
				sprite->SetTexture(tex);

				bullcomp = new BulletComponent(Bullet, owner->GetDirection(), angle - M_PI/4);
				coll = new CollisionComponent(Bullet);
				





				Bullet = new Entity(owner->getGame(), Entity::Type::Bullet);
				Bullet->SetPosition(BulletSpawnPoints[0].x, BulletSpawnPoints[0].y);

				sprite = new SpriteComponent(Bullet, 10.0f, 10.0f);
				tex = owner->getGame()->GetTexture("Assets/OmniBaseBullet.png");
				sprite->SetTexture(tex);





				bullcomp = new BulletComponent(Bullet, owner->GetDirection(), angle - M_PI/8);
				coll = new CollisionComponent(Bullet);
				


				Bullet = new Entity(owner->getGame(), Entity::Type::Bullet);
				Bullet->SetPosition(BulletSpawnPoints[0].x, BulletSpawnPoints[0].y);

				sprite = new SpriteComponent(Bullet, 10.0f, 10.0f);
				tex = owner->getGame()->GetTexture("Assets/OmniBaseBullet.png");
				sprite->SetTexture(tex);





				bullcomp = new BulletComponent(Bullet, owner->GetDirection(), angle);
				coll = new CollisionComponent(Bullet);

				
				AbleToFire = 0;

				

			}
			else
			{

			}

		}
		else
		{

		}

		

		keysPressed.pop_back();

	}



}