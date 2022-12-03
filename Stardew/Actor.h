#pragma once

#include <SDL_image.h>
#include <string>
#include "BoundingBox.h"

class Actor
{
public:
	Actor(std::string filename,
		float x, float y, int width, int height);

	virtual void draw(int scrollX = 0, int scrollY = 0);

	bool isOverlapping(Actor* actor);
	bool containsPoint(int pointX, int pointY);

	bool clicked = false;

	float x, y, vx, vy; //velocidad en x e y
	int width, height, fileWidth, fileHeight;
	SDL_Texture* texture;

	void sweep(std::unordered_set<Actor*> actors);

	float originalX;
	float originalY;
	void resetPosition();

	BoundingBox boundingBox;
};

