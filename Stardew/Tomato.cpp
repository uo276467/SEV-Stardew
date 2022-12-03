#include "Tomato.h"

Tomato::Tomato(float x, float y)
	:Crop("res/tomato_seed.png", x, y) {
	daysToGrow = 4;
	cost = 30;
	value = 60;
	name = "tomato";
}
