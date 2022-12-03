#include "Hoe.h"

Hoe::Hoe(float x, float y, int height, int width) :
	Tool("res/disparo_hoe.png", x, y, height, width) {

	name = "Hoe";

}

void Hoe::processField(Field* field) {
	if (field->state == FieldState::Grass) {
		field->plow();
	}
}
