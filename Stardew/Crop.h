#pragma once

#include "InvItem.h"
#include "Field.h"
#include <string>

enum class CropState {
	Seed,
	Growing,
	Completed,
	Croppped,
	NotWatered,
	Rotten
};

class Crop : public Actor
{
public:
	Crop(std::string texture, float x, float y);
	Crop(InvItem* item, float x, float y);

	std::string name;
	std::string estado;
	int daysToGrow;
	int daysCompleted = 0;
	int daysWithoutWater = 0;
	bool isWatered = false;
	int cost;
	int value;

	int seedLifeTime = 5;

	void update();
	void plant(Field* field);
	void water();
	void grow();
	
	CropState state = CropState::Seed;
};

