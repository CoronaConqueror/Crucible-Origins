#include "EnemyAIComponent.h"

EnemyAIComponent::EnemyAIComponent(Entity* o, EnemyType t)
{
	owner = o;

	deltax = 0.0f;
	deltay = 0.0f;
	velocity = BASEENEMYVEL;

	componentname = NAME;

	movementtimer = 1.0f; //1.0 second movement cooldown on spawn
	canMove = 0;

	type = t;

	owner->AddComponent(this);
}

EnemyAIComponent::~EnemyAIComponent()
{


}


void EnemyAIComponent::Update(float deltatime)
{

	Vect2 pos;
	pos = owner->GetPosition();

	//based on enemy type, make the enemy move and behave a certain way
	deltay += BASEGRAVITY * deltatime;

	if (deltay > TERMINALVEL)
	{
		deltay = TERMINALVEL;
	}


	if (type == EnemyAIComponent::EnemyType::ROD) //if this enemy is a ROD follow player endlessly
	{
		//std::cout << movementtimer << std::endl;
	




		if (movementtimer > 0.0f && canMove == 0)
		{
			movementtimer -= deltatime;
		}
		else if (movementtimer < 0.0f && canMove == 0)
		{
			movementtimer = 0.5f; //movement speed cooldown on stopping
			canMove = 1; //can move now
		}

		if (canMove == 1)
		{
			if (owner->GetPosition().x < owner->getGame()->GetOmni()->GetPosition().x ) //if enemy is to the left of omni and moving right
			{
				deltax += velocity * deltatime;
			}
			

			if (owner->GetPosition().x > owner->getGame()->GetOmni()->GetPosition().x)
			{
				deltax += -velocity * deltatime;
			}
			

			if (deltax > MAXENEMYVEL)
			{
				deltax = MAXENEMYVEL;
			}
			else if (deltax < -MAXENEMYVEL)
			{
				deltax = -MAXENEMYVEL;
			}


			if (deltax >= -0.075f && deltax <= 0.075f)
			{
				deltax = 0.0f;
				canMove = 0;
			}

		
			


		}

		

		

	}





	//friction, slowem down
	if (deltax > 0.0f && deltax != 0.0f)
	{
		deltax -= FRICTION * deltatime;
	}

	if (deltax < 0.0f && deltax != 0.0f)
	{
		deltax += FRICTION * deltatime;
	}





	if (pos.x > (LEVELSIZEX - owner->GetComponent("SPRITE")->GetTextureSize().x))
	{
		pos.x = (LEVELSIZEX - owner->GetComponent("SPRITE")->GetTextureSize().x);
		deltax = 0.0f;
		//deltax = -deltax;
		owner->SetPosition(pos.x + deltax, pos.y + deltay);




	}
	else if (pos.x < 0)
	{
		pos.x = 0;

		deltax = 0.0f;
		//deltax = -deltax;

		owner->SetPosition(pos.x + deltax, pos.y + deltay);
	}
	else if (pos.y < 0)
	{
		pos.y = 0;

		deltay = 0.0f;
		//deltay = -deltay;

		owner->SetPosition(pos.x + deltax, pos.y + deltay);
	}
	else if (pos.y > (LEVELSIZEY - owner->GetComponent("SPRITE")->GetTextureSize().y))
	{
		pos.y = (LEVELSIZEY - owner->GetComponent("SPRITE")->GetTextureSize().y);

		deltay = 0.0f;
		//deltay = -deltay;

		Jumping = 0;
		owner->SetPosition(pos.x + deltax, pos.y + deltay);


	}
	else
	{
		owner->SetPosition(pos.x + deltax, pos.y + deltay);
	}





}