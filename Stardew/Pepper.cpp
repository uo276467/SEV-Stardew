#include "Pepper.h"

Pepper::Pepper(float x, float y)
	:Crop("res/pepper_seed.png", x, y) {
	daysToGrow = 3;
	cost = 20;
	value = 40;
	name = "pepper";
}
