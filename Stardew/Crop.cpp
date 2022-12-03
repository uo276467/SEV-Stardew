#include "Crop.h"
#include "Game.h"


Crop::Crop(std::string texture, float x, float y)
	: Actor(texture, x, y, 32, 32) {
	estado = "seed";
}

//Crop::Crop(InvItem* item, float x, float y)
//	: Crop("res/" + item->name + "_" + item->type + ".png", 1, 1) {
//	if (item->name == "pepper") {
//		daysToGrow = 3;
//		cost = 20;
//		value = 40;
//	}
//	else  {
//
//	}
//
//}

void Crop::update() {
	if (state == CropState::Seed) {
		if (seedLifeTime > 0) {
			seedLifeTime--;
		}
	}
}

void Crop::plant(Field* field) {
	x = field->x;
	y = field->y;
	field->crop = this;
}

void Crop::water() {
	isWatered = true;
}

void Crop::grow() {
	switch (state){
	case CropState::Seed:
		if (isWatered) {
			daysCompleted++;
			state = CropState::Growing;
			estado = "growing";
			texture = Game::getTexture("res/brote.png");
		}
		else {
			state = CropState::NotWatered;
			estado = "not watered";
		}
		break;
	case CropState::Growing:
		texture = Game::getTexture("res/brote.png");
		if (isWatered) {
			daysCompleted++;
			if (daysCompleted == daysToGrow) {
				state = CropState::Completed;
				estado = "completed";
				texture = Game::getTexture("res/" + name + "_crop.png");
			}
		}
		else {
			state = CropState::NotWatered;
			estado = "not watered";
		}
		break;
	case CropState::NotWatered:
		if (isWatered) {
			state = CropState::Growing;
			texture = Game::getTexture("res/brote.png");
			estado = "growing";
			daysCompleted++;
		}
		else {
			state = CropState::Rotten;
			estado = "rotten";
			texture = Game::getTexture("res/rotten_crop.png");
		}
		break;
	}
	isWatered = false;
}
