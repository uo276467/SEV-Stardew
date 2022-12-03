#include "Field.h"
#include "Game.h"
#include "Crop.h"

Field::Field(std::string texture, float x, float y)
	: Actor(texture, x, y, 40, 40) {

}

bool Field::canBePlanted() {
	return crop == nullptr && state != FieldState::Grass;
}

void Field::grass() {
	state = FieldState::Grass;
	texture = Game::getTexture("res/hierba.png");
}

void Field::plow() {
	state = FieldState::Plow;
	texture = Game::getTexture("res/harado.png");
}

void Field::water() {
	state = FieldState::Watered;
	texture = Game::getTexture("res/regado.png");
	if (crop != nullptr) {
		crop->water();
	}
}

void Field::nextDay() {
	if (crop != nullptr) {
		crop->grow();
		plow();
	}
	else {
		if (state == FieldState::Watered) {
			plow();
		}
		else if (state == FieldState::Plow) {
			grass();
		}
	}
}