#include "CropBuyer.h"

CropBuyer::CropBuyer(float x, float y)
	:Actor("res/comprador_cultivos.png", x, y, 50, 50) {
	animation = new Animation("res/comprador_cultivos_idle.png", width, height,
		800, 50, 6, 16);
}

void CropBuyer::update() {
	animation->update();
}

void CropBuyer::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}
