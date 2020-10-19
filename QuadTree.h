#pragma once
//this class if for a quadtree implementation for collision detection
#include "Game.h"
/*

class QuadTree
{
public:

	QuadTree(int pLevel, SDL_Rect pBounds)
	{
		level = pLevel;
		bounds = pBounds;
		//nodes.reserve(4);
		//objects.reserve(10);
		nodes[0] = nullptr;
		nodes[1] = nullptr;
		nodes[2] = nullptr;
		nodes[3] = nullptr;
		objects.clear();
	}



	void clear()
	{
		objects.clear();

		for (int i = 0; i < 4; i++)
		{
			if (nodes[i] != nullptr  )
			{
				nodes[i]->clear();
				nodes[i] = nullptr;
			}
		}

	}

	void split()
	{
		int subWidth = (bounds.w / 2);
		int subHeight = (bounds.h / 2);
		int x = bounds.x;
		int y = bounds.y;

		bounds = { x + subWidth, y, subWidth, subHeight };
		nodes[0] = new QuadTree(level + 1, bounds);

		bounds = { x,  y, subWidth, subHeight };
		nodes[1] = new QuadTree(level + 1, bounds);

		bounds = { x, y + subHeight, subWidth, subHeight };
		nodes[2] = new QuadTree(level + 1, bounds);

		bounds = { x + subWidth, y + subHeight, subWidth, subHeight };
		nodes[3] = new QuadTree(level + 1, bounds);


	}


	int getIndex(SDL_Rect pRect)
	{
		int index = -1;
		double verticalMidpoint = bounds.x + (bounds.w / 2);
		double horizontalMidpoint = bounds.y + (bounds.h / 2);

		//object fits in top quadrants
		bool topQuad = (pRect.y < horizontalMidpoint&& pRect.y + pRect.h < horizontalMidpoint);
		//object fits in bottom quadrants
		bool botQuad = (pRect.y > horizontalMidpoint);

		//object completely fits in left quad
		if (pRect.x < verticalMidpoint && pRect.x + pRect.w < verticalMidpoint)
		{
			if (topQuad)
			{
				index = 1;
			}
			else if (botQuad)
			{
				index = 2;
			}
		}
		else if (pRect.x > verticalMidpoint)
		{
			if (topQuad)
			{
				index = 0;
			}
			else if (botQuad)
			{
				index = 3;
			}
		}

		return index;

	}

	//pObj is the actual entity, pRect is the hitbox for that object
	void insert(Entity* pObj)
	{
		if (nodes[0] != nullptr)
		{
			int index = getIndex(pObj->GetComponent("SPRITE")->getHITBOX());

			if (index != -1)
			{
				nodes[index]->insert(pObj);
				return;
			}
		}

		objects.emplace_back(pObj);

		if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
		{
			if (nodes[0] == nullptr)
			{
				split();
			}

			int i = 0;
			while (i < objects.size())
			{
				int index = getIndex(objects.back()->GetComponent("SPRITE")->getHITBOX());

				if (index != -1)
				{
					nodes[index]->insert(objects.back());
					objects.pop_back();
				}
				else
				{
					i++;
				}
			}


		}

	}

	void retrieve(std::vector<Entity*>* returnObjs, Entity* pObj)
	{
		if (nodes[0] != nullptr)
		{
			int index = getIndex(pObj->GetComponent("SPRITE")->getHITBOX());
			if (index != -1)
			{
				nodes[index]->retrieve(returnObjs, pObj);

			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					nodes[i]->retrieve(returnObjs, pObj);
				}
			}
		}

		for(auto o : objects)
			returnObjs->emplace_back(o);


	}




private:
	//max num of objects in a node
	int MAX_OBJECTS = 10;

	//max number of splits a tree can do
	int MAX_LEVELS = 6;

	//holds the spilt level 0-4
	int level;

	//vector of all the entities in the quadtree
	std::vector<Entity*> objects;

	SDL_Rect bounds;

	//holds the 4 sub nodes
	QuadTree* nodes[4];



};

*/
