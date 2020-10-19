#pragma once
#include "Component.h"
#include "SDL.h"
#include <vector>

class InputComponent : public Component
{
	//this component handles all of the keyboard and mouse input for any entity
	//it checks what key/keys are pressed and saves them into a vector for that frame
	//next frame it deletes the vector and starts over

public:

	const std::string NAME = "INPUT";

	InputComponent(Entity* o);
	~InputComponent();
	void Update(float deltatime) override;

	//return mouse position
	//Vect2 getMousePosition();

	std::vector<int> GetKeys() override
	{
		return keysPressed;
	}

	std::vector<int> getKeysPressed();

	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }


private:

	//this vector holds the keys that are pressed for this frame
	//it can be checked by other components to handle actions (like movement)
	std::vector<int> keysPressed;
	
	//holds the mouse position for other components to use
	//Vect2 mousePosition;

	//holds the mouse buttons pressed this frame
	//std::vector<int> mouseButtonsPressed;

	Entity* owner;

	std::string componentname;
};