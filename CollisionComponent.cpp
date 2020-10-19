#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Entity* o)
{
	owner = o;
	componentname = NAME;

	HitBox = new SDL_Rect();

	HitBox->x = owner->GetPosition().x;
	HitBox->y = owner->GetPosition().y;
	HitBox->w = owner->GetComponent("SPRITE")->GetTextureSize().x;
	HitBox->h = owner->GetComponent("SPRITE")->GetTextureSize().y;
	


	//HitBox = { static_cast<int>(owner->GetPosition().x), static_cast<int>(owner->GetPosition().y), static_cast<int>(owner->GetComponent("SPRITE")->GetTextureSize().x), static_cast<int>(owner->GetComponent("SPRITE")->GetTextureSize().y) };
	

	
	owner->AddComponent(this);
}

CollisionComponent::~CollisionComponent()
{

}




void CollisionComponent::Update(float deltatime)
{
	HitBox->x = owner->GetPosition().x;
	HitBox->y = owner->GetPosition().y;
	HitBox->w = owner->GetComponent("SPRITE")->GetTextureSize().x;
	HitBox->h = owner->GetComponent("SPRITE")->GetTextureSize().y;
	
	//std::cout << owner->GetCollisionsThisFrame().size() << std::endl;

	for (auto ent : owner->GetCollisionsThisFrame())
	{
		CheckCollisions(ent);

	}
			


}



		





void CollisionComponent::CheckCollisions(Entity* ent)
{

	//SDL_Rect HitBox;
	SDL_Rect* OtherHitBox;
	OtherHitBox = new SDL_Rect();
	std::string sideHit = "blank";


	

	HitBox->x = owner->GetPosition().x;
	HitBox->y = owner->GetPosition().y;
	HitBox->w = owner->GetComponent("SPRITE")->GetTextureSize().x;
	HitBox->h = owner->GetComponent("SPRITE")->GetTextureSize().y;


	OtherHitBox->x = ent->GetPosition().x;
	OtherHitBox->y = ent->GetPosition().y;
	OtherHitBox->w = ent->GetComponent("SPRITE")->GetTextureSize().x;
	OtherHitBox->h = ent->GetComponent("SPRITE")->GetTextureSize().y;

	//HitBox = { static_cast<int>(owner->GetPosition().x), static_cast<int>(owner->GetPosition().y), static_cast<int>(owner->GetComponent("SPRITE")->GetTextureSize().x), static_cast<int>(owner->GetComponent("SPRITE")->GetTextureSize().y) };
	


	//OtherHitBox = { static_cast<int>(ent->GetPosition().x), static_cast<int>(ent->GetPosition().y), static_cast<int>(ent->GetComponent("SPRITE")->GetTextureSize().x), static_cast<int>(ent->GetComponent("SPRITE")->GetTextureSize().y) };


	//OtherHitBox = ent->GetComponent("COLLISION")->GetHitBox();
	//OtherHitBox->x = ent->GetPosition().x;
	//OtherHitBox->y = ent->GetPosition().y;


	//HitBox->x = ent->GetPosition().x;
	//HitBox->y = ent->GetPosition().y;

	//std::cout << "Bruh" << std::endl;
	if (SDL_HasIntersection(HitBox, OtherHitBox) == true) //true means there was a collision
	{
		//std::cout << ent->GetType() << std::endl;



		if (owner->GetType() == Entity::Type::Player) //ENT IS THE PLAYER      OWNER IS THE THING BEING COLLIDED WITH
		{
			//std::cout << "Collision Detected" << std::endl;
			if (ent->GetType() == Entity::Type::Bullet) //ent is player bullet
			{
				//ignore own bullet collision
				//std::cout << "Player Colliding with own bullet" << std::endl;

			}
			else if (ent->GetType() == Entity::Type::Platform) //ent is platform
			{
				//hit platform, prevent moving into platform, enforce the hit box
				//std::cout << "Player Colliding with platform" << std::endl;



				//owner->GetComponent("MOVEMENT")->SetDeltaY(owner->GetComponent("MOVEMENT")->GetDeltaY() - (sin(owner->GetComponent("MOVEMENT")->GetAngle())));
				//owner->GetComponent("MOVEMENT")->SetDeltaX(owner->GetComponent("MOVEMENT")->GetDeltaX() - (cos(owner->GetComponent("MOVEMENT")->GetAngle())));





				//check over platform or under platform
				sideHit = CheckSide(*HitBox, *OtherHitBox);

				//std::cout << sideHit << std::endl;


				if (sideHit == "Top")
				{
					//ent->SetPosition(HitBox->x, HitBox->y - (HitBox->y + HitBox->h - OtherHitBox->y));

					owner->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
					owner->GetComponent("MOVEMENT")->SetJumping(0);
					owner->SetPosition(HitBox->x, HitBox->y - (HitBox->y + HitBox->h - OtherHitBox->y));

				}
				else if (sideHit == "Bottom")
				{

					owner->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
					owner->SetPosition(HitBox->x, OtherHitBox->y + OtherHitBox->h);
					//break;

				}
				else if (sideHit == "Left")
				{

					owner->GetComponent("MOVEMENT")->SetDeltaX(0.0f); //stop horizontal momentum
					owner->SetPosition(HitBox->x - (HitBox->x + HitBox->w - OtherHitBox->x), HitBox->y);

				}
				else if (sideHit == "Right" && HitBox->x < OtherHitBox->x + (OtherHitBox->w * 0.90f))
				{
					owner->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
					owner->GetComponent("MOVEMENT")->SetJumping(0);
					owner->SetPosition(HitBox->x, HitBox->y - (HitBox->y + HitBox->h - OtherHitBox->y));

				}
				else if (sideHit == "Right")
				{
					owner->GetComponent("MOVEMENT")->SetDeltaX(0.0f); //stop horizontal momentum
					owner->SetPosition(OtherHitBox->w + OtherHitBox->x, HitBox->y);
				}



				//owner->GetComponent("MOVEMENT")->GetDeltaY() > 13.0f && (HitBox->y + (HitBox->h / 1.10f) > OtherHitBox->y)









			}



		}


		if (owner->GetType() == Entity::Type::Bullet) //ent is player bullet
		{

			//std::cout << "bullet collision" << std::endl;
			if (ent->GetType() == Entity::Type::Platform) //bullet hit a platform
			{
				//std::cout << "bullet hit platform" << std::endl;
				owner->SetState(Entity::State::Dead); //kill the bullet
			}
		}

		if (owner->GetType() == Entity::Type::Enemy) //ent is an enemy
		{

			if (ent->GetType() == Entity::Type::Bullet) //owner is player bullet
			{

				//std::cout << "enemy Colliding with omni bullet" << std::endl;








			}
			else if (ent->GetType() == Entity::Type::Platform) //owner is platform
			{
				//hit platform, prevent moving into platform, enforce the hit box
				//std::cout << "enemy Colliding with platform" << std::endl;


				//				CHANGE ALL COMPONENT REFERENCES WITH ENEMY AI COMPONENT REFERENCES




			}

		}

		if (owner->GetType() == Entity::Type::Platform) //owner is an enemy bullet
		{
			if (ent->GetType() == Entity::Type::Bullet)
			{
				ent->SetState(Entity::State::Dead);
			}

		}




	}
	else
	{

	}




	delete OtherHitBox; //memory leak was here!!!

}











std::string CollisionComponent::CheckSide(SDL_Rect owner, SDL_Rect ent)
{
	//these entities collided, I need to find the side that owner hit
	//ex: owner hit left side of platform, owner hit bottom of platform

	//y = 1.10f
	//y = 5.0f





	if ((owner.y + owner.h > ent.y && owner.y + (owner.h / 1.10f) < ent.y) && ((owner.x + owner.w > ent.x) && (owner.x < ent.x + ent.w)))
	{
		return "Top";
	}
	else if ((owner.y < ent.y + ent.h && owner.y + (owner.h / 5.0f)  > ent.y + ent.h) && ((owner.x + owner.w > ent.x) && (owner.x < ent.x + ent.w)))
	{
		return "Bottom";
	}
	else if (owner.x + owner.w > ent.x && owner.x < ent.x)
	{
		return "Left";
	}
	else
	{
		return "Right";
	}



	/*
	if ((owner->y + owner->h > ent->y && owner->y + (owner->h/1.10f) < ent->y) && ((owner->x + owner->w > ent->x) && (owner->x < ent->x + ent->w)))
	{
		return "Top";
	}
	else if ((owner->y < ent->y + ent->h && owner->y + (owner->h / 5.0f)  > ent->y + ent->h) && ((owner->x + owner->w > ent->x) && (owner->x < ent->x + ent->w)))
	{
		return "Bottom";
	}
	else if (owner->x + owner->w > ent->x && owner->x < ent->x)
	{
		return "Left";
	}
	else
	{
		return "Right";
	}
	*/
	//std::cout << "Middle" << std::endl;








}




















/*


void CollisionComponent::Update(float deltatime)
{
	/*
	MidPoint.x = owner->GetPosition().x + (owner->GetComponent("SPRITE")->GetTextureSize().x / 2);
	MidPoint.y = owner->GetPosition().y + (owner->GetComponent("SPRITE")->GetTextureSize().y / 2);

	
	//check to see if entity has collision component
bool HasCollision;
SDL_Rect* OtherHitBox;
std::string sideHit = "blank";
float biggestLengthO = 0.0f;
float biggestLengthE = 0.0f;
float biggestLength = 0.0f;
std::vector<Entity*> possiblecoll;
//holds coordinates before collision
//Vect2 OldOwnerCoor = owner->GetPosition();




//std::cout << possiblecoll.size() << std::endl;
//check for collision with each other entity with collision components

for (auto ent : owner->getGame()->GetEntities())
{

	/*
	MidPoint.x = owner->GetPosition().x + (owner->GetComponent("SPRITE")->GetTextureSize().x / 2);
	MidPoint.y = owner->GetPosition().y + (owner->GetComponent("SPRITE")->GetTextureSize().y / 2);

	OMidPoint.x = ent->GetPosition().x + (ent->GetComponent("SPRITE")->GetTextureSize().x / 2);
	OMidPoint.y = ent->GetPosition().y + (ent->GetComponent("SPRITE")->GetTextureSize().y / 2);

	float dx = OMidPoint.x - MidPoint.x;
	float dy = OMidPoint.y - MidPoint.y;
	



	MidPoint.x = ent->GetPosition().x + (ent->GetComponent("SPRITE")->GetTextureSize().x / 2);
	MidPoint.y = ent->GetPosition().y + (ent->GetComponent("SPRITE")->GetTextureSize().y / 2);

	OMidPoint.x = owner->GetPosition().x + (owner->GetComponent("SPRITE")->GetTextureSize().x / 2);
	OMidPoint.y = owner->GetPosition().y + (owner->GetComponent("SPRITE")->GetTextureSize().y / 2);

	float dx = OMidPoint.x - MidPoint.x;
	float dy = OMidPoint.y - MidPoint.y;


	float distanceSQR = ((dx * dx) + (dy * dy));



	if (ent->GetComponent("SPRITE")->GetTextureSize().y >= ent->GetComponent("SPRITE")->GetTextureSize().x)
	{
		biggestLengthE = ent->GetComponent("SPRITE")->GetTextureSize().y;
	}
	else
	{
		biggestLengthE = ent->GetComponent("SPRITE")->GetTextureSize().x;
	}


	if (owner->GetComponent("SPRITE")->GetTextureSize().y >= owner->GetComponent("SPRITE")->GetTextureSize().x)
	{
		biggestLengthO = owner->GetComponent("SPRITE")->GetTextureSize().y;
	}
	else
	{
		biggestLengthO = owner->GetComponent("SPRITE")->GetTextureSize().x;
	}

	if (biggestLengthE > biggestLengthO)
	{
		biggestLength = biggestLengthE;
	}
	else
	{
		biggestLength = biggestLengthO;
	}



	if (distanceSQR < (biggestLength * biggestLength))
	{
		//std::cout << distanceSQR << std::endl;

		HasCollision = ent->HasComponent("COLLISION");

		if (HasCollision != 0 && owner != ent)//if that entity has a collision component
		{
			//check the hitbox of that entity with this entity for collision
			HitBox->x = owner->GetPosition().x;
			HitBox->y = owner->GetPosition().y;

			OtherHitBox = ent->GetComponent("COLLISION")->GetHitBox();
			OtherHitBox->x = ent->GetPosition().x;
			OtherHitBox->y = ent->GetPosition().y;


			//HitBox->x = ent->GetPosition().x;
			//HitBox->y = ent->GetPosition().y;

			//std::cout << "Bruh" << std::endl;
			if (SDL_HasIntersection(OtherHitBox, HitBox) == true) //true means there was a collision
			{
				//std::cout << ent->GetType() << std::endl;

				if (ent->GetType() == Entity::Type::Player) //ENT IS THE PLAYER      OWNER IS THE THING BEING COLLIDED WITH
				{
					//std::cout << "Collision Detected" << std::endl;
					if (owner->GetType() == Entity::Type::Bullet) //ent is player bullet
					{
						//ignore own bullet collision
						//std::cout << "Player Colliding with own bullet" << std::endl;
					}
					else if (owner->GetType() == Entity::Type::Platform) //ent is platform
					{
						//hit platform, prevent moving into platform, enforce the hit box
						//std::cout << "Player Colliding with platform" << std::endl;



						//owner->GetComponent("MOVEMENT")->SetDeltaY(owner->GetComponent("MOVEMENT")->GetDeltaY() - (sin(owner->GetComponent("MOVEMENT")->GetAngle()))); 
						//owner->GetComponent("MOVEMENT")->SetDeltaX(owner->GetComponent("MOVEMENT")->GetDeltaX() - (cos(owner->GetComponent("MOVEMENT")->GetAngle())));





						//check over platform or under platform
						sideHit = CheckSide(OtherHitBox, HitBox);

						//std::cout << sideHit << std::endl;


						if (sideHit == "Top")
						{
							//ent->SetPosition(HitBox->x, HitBox->y - (HitBox->y + HitBox->h - OtherHitBox->y));

							ent->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
							ent->GetComponent("MOVEMENT")->SetJumping(0);
							ent->SetPosition(OtherHitBox->x, OtherHitBox->y - (OtherHitBox->y + OtherHitBox->h - HitBox->y));

						}
						else if (sideHit == "Bottom")
						{

							ent->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
							ent->SetPosition(OtherHitBox->x, HitBox->y + HitBox->h);
							//break;

						}
						else if (sideHit == "Left")
						{

							ent->GetComponent("MOVEMENT")->SetDeltaX(0.0f); //stop horizontal momentum
							ent->SetPosition(OtherHitBox->x - (OtherHitBox->x + OtherHitBox->w - HitBox->x), OtherHitBox->y);

						}
						else if (sideHit == "Right" && OtherHitBox->x < HitBox->x + (HitBox->w * 0.90f))
						{
							ent->GetComponent("MOVEMENT")->SetDeltaY(0.0f); //stop vertical momentum
							ent->GetComponent("MOVEMENT")->SetJumping(0);
							ent->SetPosition(OtherHitBox->x, OtherHitBox->y - (OtherHitBox->y + OtherHitBox->h - HitBox->y));

						}
						else if (sideHit == "Right")
						{
							ent->GetComponent("MOVEMENT")->SetDeltaX(0.0f); //stop horizontal momentum
							ent->SetPosition(HitBox->w + HitBox->x, OtherHitBox->y);
						}



						//owner->GetComponent("MOVEMENT")->GetDeltaY() > 13.0f && (HitBox->y + (HitBox->h / 1.10f) > OtherHitBox->y)









					}



				}

				if (ent->GetType() == Entity::Type::Bullet) //ent is player bullet
				{
					//std::cout << "bullet hit platform" << std::endl;
					if (owner->GetType() == Entity::Type::Platform) //bullet hit a platform
					{
						ent->SetState(Entity::State::Dead); //kill the bullet
					}
				}

				if (ent->GetType() == Entity::Type::Enemy) //ent is an enemy
				{

					if (owner->GetType() == Entity::Type::Bullet) //owner is player bullet
					{

						//std::cout << "enemy Colliding with omni bullet" << std::endl;








					}
					else if (owner->GetType() == Entity::Type::Platform) //owner is platform
					{
						//hit platform, prevent moving into platform, enforce the hit box
						//std::cout << "enemy Colliding with platform" << std::endl;


						//				CHANGE ALL COMPONENT REFERENCES WITH ENEMY AI COMPONENT REFERENCES


						sideHit = CheckSide(OtherHitBox, HitBox);

						std::cout << sideHit << std::endl;


						if (sideHit == "Top")
						{
							//ent->SetPosition(HitBox->x, HitBox->y - (HitBox->y + HitBox->h - OtherHitBox->y));

							ent->GetComponent("ENEMYAI")->SetDeltaY(0.0f); //stop vertical momentum
							//ent->GetComponent("MOVEMENT")->SetJumping(0);
							ent->SetPosition(OtherHitBox->x, OtherHitBox->y - (OtherHitBox->y + OtherHitBox->h - HitBox->y));

						}
						else if (sideHit == "Bottom")
						{

							ent->GetComponent("ENEMYAI")->SetDeltaY(0.0f); //stop vertical momentum
							ent->SetPosition(OtherHitBox->x, HitBox->y + HitBox->h);
							//break;

						}
						else if (sideHit == "Left")
						{

							ent->GetComponent("ENEMYAI")->SetDeltaX(0.0f); //stop horizontal momentum
							ent->SetPosition(OtherHitBox->x - (OtherHitBox->x + OtherHitBox->w - HitBox->x), OtherHitBox->y);

						}
						else if (sideHit == "Right" && OtherHitBox->x < HitBox->x + (HitBox->w * 0.90f))
						{
							ent->GetComponent("ENEMYAI")->SetDeltaY(0.0f); //stop vertical momentum
							//ent->GetComponent("MOVEMENT")->SetJumping(0);
							ent->SetPosition(OtherHitBox->x, OtherHitBox->y - (OtherHitBox->y + OtherHitBox->h - HitBox->y));

						}
						else if (sideHit == "Right")
						{
							ent->GetComponent("ENEMYAI")->SetDeltaX(0.0f); //stop horizontal momentum
							ent->SetPosition(HitBox->w + HitBox->x, OtherHitBox->y);
						}




					}

				}

				if (owner->GetType() == Entity::Type(5)) //owner is an enemy bullet
				{


				}



			}
			else
			{

			}


		}

		//break;

	}
	else
	{

		//break;
	}













}






possiblecoll.clear();

}





*/