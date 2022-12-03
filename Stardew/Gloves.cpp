#include "Gloves.h"
#include "Crop.h"
#include "Player.h"

Gloves::Gloves(float x, float y, int height, int width, Player* player) :
	Tool("res/disparo_gloves.png", x, y, height, width), player(player) {

	name = "Gloves";
}

void Gloves::processField(Field* field) {
	if(!player->inventory->isFull()){
		Crop* crop = field->crop;
		if (crop != nullptr) {
			if (field->crop->state == CropState::Completed) {
				InvItem* cropItem = new InvItem(crop->name, "crop", 1, crop->value);
				player->addToInventory(cropItem);
				crop->state = CropState::Croppped;
				field->crop = nullptr;
			}
			else if (field->crop->state == CropState::Rotten) {
				crop->state = CropState::Croppped;
				field->crop = nullptr;
			}
		}
	}
}
