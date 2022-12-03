#include "Eggplant.h"

Eggplant::Eggplant(float x, float y)
	:Crop("res/eggplant_seed.png", x, y) {
	daysToGrow = 7;
	cost = 60;
	value = 160;
	name = "eggplant";
}