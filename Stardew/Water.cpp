#include "Water.h"

Water::Water(float x, float y, int height, int width) :
	Tool("res/disparo_water.png", x, y, height, width) {

	name = "Water";

}

void Water::processField(Field* field) {
	if (field->state == FieldState::Plow) {
		field->water();
	}
}
