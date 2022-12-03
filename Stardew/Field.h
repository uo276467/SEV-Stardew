#pragma once
#include "Actor.h"
class Crop;

enum class FieldState {
	Grass,
	Plow,
	Watered
};

class Field : public Actor
{
public:
	Field(std::string texture, float x, float y);

	bool canBePlanted();
	void grass();
	void plow();
	void water();
	void nextDay();

	Crop* crop = nullptr;

	FieldState state = FieldState::Grass;
};