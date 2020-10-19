#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(Entity* o, float w, float h)
	:componentname(NAME)
	, owner(o)
	, texWidth(w)
	, texHeight(h)
{
	//std::cout << "sprite component added " << this << std::endl;
	//owner->getGame()->AddDrawingEntity(owner);
	
	//HITBOX = { static_cast<int>(owner->GetPosition().x), static_cast<int>(owner->GetPosition().y), static_cast<int>(w), static_cast<int>(h) };
	owner->AddComponent(this);
}

SpriteComponent::~SpriteComponent()
{

	
	//std::cout << "sprite destructor called" << this << std::endl;
	RemoveTexture();
	//owner->RemoveComponent(this);
	//std::cout << "sprite destructor remove component called" << this << std::endl;
	//owner->getGame()->RemoveDrawingComponent(this);
	
	
	
}


void SpriteComponent::SetTexture(SDL_Texture* tex)
{
	texture = tex;
	//this should call to a textures vector that will store the texture
	//maybe for future use or to be destroyed later
}

void SpriteComponent::RemoveTexture()
{
	SDL_DestroyTexture(texture);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{

	if (texture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(texWidth);
		r.h = static_cast<int>(texHeight);
		// Center the rectangle around the position of the owner
		
		                   //r.x = static_cast<int>(owner->GetPosition().x - r.w / 2);
		             //r.y = static_cast<int>(owner->GetPosition().y - r.h / 2);

		if (owner->getGame()->GetRightBound() == 1) //at right bound
		{
			r.x = static_cast<int>(owner->GetPosition().x - (LEVELSIZEX/2));
		}
		else
		{
			r.x = static_cast<int>(owner->GetPosition().x - owner->getGame()->GetScreen().x);
		}

		if (owner->getGame()->GetBottomBound() == 1) //at bottom bound
		{
			r.y = static_cast<int>(owner->GetPosition().y - (LEVELSIZEY/2));
		}
		else
		{
			r.y = static_cast<int>(owner->GetPosition().y - owner->getGame()->GetScreen().y);
		}


		
		
		
		
		

		//r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		//r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		//SDL_RenderCopyEx(renderer,
			//mTexture,
			//nullptr,   source
			//&r,     destination
			//-Math::ToDegrees(mOwner->GetRotation()),
			//nullptr,
			//SDL_FLIP_NONE);

		SDL_RenderCopy(renderer, texture, nullptr, &r);


	}

}


void SpriteComponent::Update(float deltaTime)
{
	/*
	float nx = owner->GetPosition().x;
	float ny = owner->GetPosition().y;

	nx += 5.0f * deltaTime;

	ny += 5.0f * deltaTime;

	owner->SetPosition(nx, ny);
	//move the background down and right 5 pixels per second

	*/

	//HITBOX = 


}