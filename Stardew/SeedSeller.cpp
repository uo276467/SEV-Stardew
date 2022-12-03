#include "SeedSeller.h"

SeedSeller::SeedSeller(float x, float y)
	:Actor("res/vendedor_semillas.png", x, y, 50, 50) {
	animation = new Animation("res/vendedor_semillas_idle.png", width, height,
		800, 50, 6, 16);
}

void SeedSeller::update() {
	animation->update();
}

void SeedSeller::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}
