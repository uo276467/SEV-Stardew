#pragma once

#include "Actor.h"
#include "Animation.h"

class SeedSeller : public Actor
{
public:
	SeedSeller(float x, float y);
	void draw(int scrollX = 0, int scrollY = 0) override;
	void update();

	Animation* animation;
};

