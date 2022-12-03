#pragma once
#include "Actor.h"
#include "Animation.h"
class CropBuyer : public Actor
{
public:
	CropBuyer(float x, float y);
	void draw(int scrollX = 0, int scrollY = 0) override;
	void update();

	Animation* animation;
};
