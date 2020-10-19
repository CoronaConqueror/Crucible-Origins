#include "Component.h"

void Component::Update(float deltaTime)
{
	
}

std::vector<int> Component::GetKeys()
{
	return dummy1;
}

Vect2 Component::GetTextureSize()
{
	return dummy2;
}

Component::~Component()
{ 
	//std::cout << "Base Component destuctor called" << this << std::endl;
	//owner->RemoveComponent(this); 
	
}

void Component::Draw(SDL_Renderer* ren)
{
	
}

void Component::SetComponentName(std::string name)
{
	componentName = name;
	
}

std::string Component::GetComponentName()
{
	return componentName;
}

Vect2 Component::GetMidPoint()
{
	return dummy2;
}

SDL_Rect* Component::getHITBOX()
{
	return dummy3;
}

void Component::SetDeltaX(float dx)
{

}

void Component::SetDeltaY(float dy)
{

}

void Component::SetJumping(bool b)
{

}

float Component::GetDeltaY()
{
	return dummy5;
}

float Component::GetDeltaX()
{
	return dummy5;
}

float Component::GetAngle()
{
	return dummy5;
}
