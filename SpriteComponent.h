#pragma once
#include "Component.h"
#include <string>
#include "SDL_image.h"

class SpriteComponent : public Component
{
public:

	Entity* GetOwner() { return owner; }

	const std::string NAME = "SPRITE";

	SpriteComponent(Entity* o, float w, float h);

	~SpriteComponent() override;

	 //~Component();

	//draw the sprite to the screen
	void Draw(SDL_Renderer* renderer) override;
	void Update(float delaTime) override;


	//need a function to set the texture for this component
	virtual void SetTexture(SDL_Texture* tex);
	//need a function to remove the texture for this component
	void RemoveTexture();


	//return size of texture (x, y) as a vect 2
	virtual Vect2 GetTextureSize() override
	{
		Vect2 size;
		size.x = texWidth;
		size.y = texHeight;
		return size;
	}


	void SetComponentName(std::string name) override { componentname = name; }
	std::string GetComponentName() override { return componentname; }

	//SDL_Rect getHITBOX() override { return HITBOX; }


private:

	//holds the width and height for the texture
	float texWidth;
	float texHeight;

	//need a texture for this sprite
	SDL_Texture* texture;

	//name of component
	std::string componentname;

	//pointer to owner of component
	Entity* owner;

	//SDL_Rect HITBOX;




};