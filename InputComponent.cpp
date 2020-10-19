#include "InputComponent.h"
#include <iostream>

InputComponent::InputComponent(Entity* o)
	:owner(o)
{
	componentname = NAME;

	owner->AddComponent(this);
}

InputComponent::~InputComponent()
{
	//owner->RemoveComponent(this);
}

void InputComponent::Update(float deltatime)
{
	//check here? clear the vector then check keys and populate it again

	//SDL_Event e;


	//SDL_PollEvent(&e);

	const uint8_t* state = SDL_GetKeyboardState(NULL);

	keysPressed.clear();
	//mouseButtonsPressed.clear();

	if (state[SDL_SCANCODE_A]) //check if the A key is pressed currently, add it to the vector
	{
		keysPressed.emplace_back(SDL_SCANCODE_A);
	}

	if (state[SDL_SCANCODE_D])
	{
		keysPressed.emplace_back(SDL_SCANCODE_D);
	}

	if (state[SDL_SCANCODE_W])
	{
		keysPressed.emplace_back(SDL_SCANCODE_W);
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		keysPressed.emplace_back(SDL_SCANCODE_SPACE);
	}

	/*

	int x; int y;
		if (e.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&x, &y); //get mouse coordinates

			mousePosition.x = x;
			mousePosition.y = y;

			mouseButtonsPressed.emplace_back(SDL_MOUSEMOTION);

		}

		if (e.type == SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mouseButtonsPressed.emplace_back(SDL_BUTTON_LEFT);
		}


		if (e.type == SDL_MOUSEBUTTONUP)
		{
			mouseButtonsPressed.emplace_back(SDL_MOUSEBUTTONUP);
		}

		*/


	

	


	/*
	if (!keysPressed.empty())
	{
		for (auto k : keysPressed)
		{
			std::cout << keysPressed.back() << std::endl;
			keysPressed.pop_back();
		}
	}
	*/
	
	
}



//Vect2 InputComponent::getMousePosition()
//{
//	return mousePosition;
//}


std::vector<int> InputComponent::getKeysPressed()
{
	return keysPressed;
}