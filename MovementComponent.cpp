#include "MovementComponent.h"

MovementComponent::MovementComponent(Entity* o)
	:owner(o)
{

	deltax = 0.0f;
	deltay = 0.0f;

	componentname = NAME;

	owner->AddComponent(this);
}

MovementComponent::~MovementComponent()
{
	//owner->RemoveComponent(this);
}

void MovementComponent::Update(float deltatime)
{
	//get the Keys pressed on this frame from the input component
	//then put logic that moves the entity from the keys pressed that frame

	//InputComponent* IN = owner->GetComponent(1);

	//get the current screen pos and size

	Vect2 pos;
	pos = owner->GetPosition();

	screenCopy = owner->getGame()->GetScreen();

	//get the angle of the velocity
	angle = atan(deltay / deltax);

	//screenCopy.x = (pos.x + (owner->GetComp(0)->GetTextureSize().x / 2) - (SCREENSIZEX / 2));
	screenCopy.x = (pos.x + (owner->GetComponent("SPRITE")->GetTextureSize().x / 2) - (SCREENSIZEX / 2));
	screenCopy.y = (pos.y + (owner->GetComponent("SPRITE")->GetTextureSize().y / 2) - (SCREENSIZEY / 2));
	
	if(screenCopy.x < 0)
	{
		screenCopy.x = 0;
	}
	if(screenCopy.y < 0)
	{
		screenCopy.y = 0;
	}

	
	if (screenCopy.x > (LEVELSIZEX - screenCopy.x))
	{
		screenCopy.x = (LEVELSIZEX - screenCopy.x);
		owner->getGame()->SetRightBound(1);					//change this back to 1
	}
	else
	{
		owner->getGame()->SetRightBound(0);
	}

	
	if(screenCopy.y > (LEVELSIZEY - screenCopy.y))
	{
		screenCopy.y = (LEVELSIZEY - screenCopy.y);
		owner->getGame()->SetBottomBound(1);
	}
	else
	{
		owner->getGame()->SetBottomBound(0);
	}

	
	owner->getGame()->SetScreen(screenCopy);


	kPressed = owner->GetComponent("INPUT")->GetKeys();
	
	if (Jumping == 0 && Moving == 0 ) //not moving and jumping
	{
		if (deltax > 0.0f && deltax != 0.0f)
		{
			deltax -= FRICTION * deltatime;
		}

		if (deltax < 0.0f && deltax != 0.0f)
		{
			deltax += FRICTION * deltatime;
		}

		/*
		if (deltay > 0.0f && deltay != 0.0f)
		{
			deltay -= FRICTION * deltatime;
		}

		if (deltay < 0.0f && deltay != 0.0f)
		{
			deltay += FRICTION * deltatime;
		}
		*/
	}

	




	if (deltax >= -0.05f && deltax <= 0.05f)
	{
		deltax = 0.0f;
	}

	if (deltay >= -0.05f && deltay <= 0.05f)
	{
		deltay = 0.0f;
	
	}

	while (!kPressed.empty())
	{
		int temp = 0;
		temp = kPressed.back();

		if (temp == SDL_SCANCODE_A) //A key pressed
		{
			deltax -= OMNIACCELERATION * deltatime;; //move left
			owner->SetDirection(0);
			Moving = 1;
		}
		else if(temp == SDL_SCANCODE_D)
		{
			deltax += OMNIACCELERATION * deltatime; //move right
			owner->SetDirection(1);
			Moving = 1;
		}
		else if (temp == SDL_SCANCODE_W && Jumping == 0)
		{
			deltay -= OMNIJUMP; //move up
			Jumping = 1;
			
		}

		Moving = 0;
	

		kPressed.pop_back();

	}

	//temporary gravity
	deltay += (BASEGRAVITY * deltatime);



	//enforce max speeds
	if (deltax > MAXOMNIVEL)
	{
		deltax = MAXOMNIVEL;
	}

	if (deltax < -MAXOMNIVEL)
	{
		deltax = -MAXOMNIVEL;
	}

	if (deltay > TERMINALVEL)
	{
		deltay = TERMINALVEL;
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

	

	

	





	/*
	if (!kPressed.empty())
	{
		for (auto k : kPressed)
		{
			std::cout << " MOVE COMP " << kPressed.back() << std::endl;
			kPressed.pop_back();
		}
	}
	*/
	
	


}