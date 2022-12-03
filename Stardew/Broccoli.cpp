#include "Broccoli.h"

Broccoli::Broccoli(float x, float y)
	:Crop("res/broccoli_seed.png", x, y) {
	daysToGrow = 6;
	cost = 50;
	value = 100;
	name = "broccoli";
}
