#include "Potato.h"

Potato::Potato(float x, float y)
	:Crop("res/potato_seed.png", x, y) {
	daysToGrow = 5;
	cost = 40;
	value = 80;
	name = "potato";
}
