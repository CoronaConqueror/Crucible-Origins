
#pragma once


#include <string>
#include <iostream>


#include "Entity.h"

class Entity;


class Component
{
public:
	

	Component()
		:componentName("Blank")
		,owner(nullptr)
	{}

	Component(std::string n, Entity* o)
		:componentName(n)
		,owner(o)
	{}

	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual std::vector<int> GetKeys();
	virtual Vect2 GetTextureSize();
	virtual void Draw(SDL_Renderer* ren);
	virtual Vect2 GetMidPoint();
	virtual SDL_Rect* getHITBOX();
	virtual void SetDeltaX(float dx);
	virtual void SetDeltaY(float dy);
	virtual void SetJumping(bool b);
	virtual float GetDeltaY();
	virtual float GetDeltaX();
	virtual float GetAngle();



	//void setComponentName(std::string name) { componentName = name; }
	//std::string getComponentName() { return componentName; }

	virtual void SetComponentName(std::string name);
	virtual std::string GetComponentName();



	//overload the == operator to check from component equality???
	friend bool operator==(Component a, Component b)
	{
		if (a.componentName == b.componentName)
		{
			//they are the same component then
			return true;
		}
		else
		{
			// if the names don't match, then the components are different...
			return false;
		}
	}

private:
	//string to identify what kind of component this is?
	std::string componentName;

	//identifies the owner of the componenet
	class Entity* owner;


	//dummy variables
	std::vector<int> dummy1;
	Vect2 dummy2;

	SDL_Rect* dummy3;
	bool dummy4;
	float dummy5;

};