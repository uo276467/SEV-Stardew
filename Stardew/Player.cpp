#include "Player.h"

Player::Player(float x, float y)
	: Actor("res/jugador.png", x, y, 35, 35) {
	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8);
	animation = aIdleRight;
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8);
	aShootingRight = new Animation("res/jugador_disparando_derecha.png", width, height,
		160, 40, 6, 4, false);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png", width, height,
		160, 40, 6, 4, false);

	inventory = new Inventory();
}

void Player::update() {

	bool animationEnded = animation->update();

	if (vx > 0) {	//si nos movemos a la derecha
		orientation = Orientation::Right;
	}
	else if (vx < 0) {	//si nos movemos a la izquierda
		orientation = Orientation::Left;
	}

	if (animationEnded) {
		if (state == State::DoingAction) {
			state = State::Moving;
		}
	}

	switch (state) {
	case State::DoingAction:
		animation = orientation == Orientation::Right ? aShootingRight : aShootingLeft;
		break;
	case State::Moving:
		if (vx == 0 && vy == 0) {	//si estamos parados
			animation = orientation == Orientation::Right ? aIdleRight : aIdleLeft;
		}
		else {
			animation = orientation == Orientation::Right ? aRunningRight : aRunningLeft;
		}
		break;
	}

	if (actionTime > 0) {
		actionTime--;
	}
}

void Player::selectFromInventory(int index) {
	inventory->select(index);
}

InvItem* Player::selectedItem() {
	return inventory->selectedItem;
}

InvItem* Player::getFromInventory(int index) {
	return inventory->getItemAt(index);
}

bool Player::isSelectedTool() {
	if(inventory->selectedItem != nullptr)
		return inventory->selectedItem->type=="tool";
	return false;
}

bool Player::isSelectedSeed() {
	if (inventory->selectedItem != nullptr)
		return inventory->selectedItem->type == "seed";
	return false;
}

void Player::addToInventory(InvItem* item) {
	inventory->add(item);
}

Tool* Player::useTool() {
	InvItem* item = inventory->selectedItem;
	if (actionTime == 0) {
		state = State::DoingAction;
		actionTime = actionCadence;
		energy--;
		int ori;
		if (orientation == Orientation::Right)
			ori = 20;
		else
			ori = -20;
		return toolFactory->createTool(item, x + ori, y, this);
	}
	return nullptr;
}

Crop* Player::useSeed() {
	InvItem* item = inventory->selectedItem;
	if (actionTime == 0) {
		state = State::DoingAction;
		actionTime = actionCadence;
		energy--;
		int ori;
		if (orientation == Orientation::Right)
			ori = 20;
		else
			ori = -20;
		Crop* crop = cropFactory->createCrop(item, x + ori, y);
		selectedItem()->decUnits();
		return crop;
	}
	else {
		return nullptr;
	}
}


bool Player::hasEnergy() {
	return energy >= 1;
}

bool Player::isEntering(Casa* casa) {
	return boundingBox.isEntering(casa->boundingBox);
}

int Player::sellCrops() {
	money+= inventory->sellCrops();
	return money;
}

void Player::moveX(float direction) {
	vx = direction * 3;
}

void Player::moveY(float direction) {
	vy = direction * 3;
}

void Player::resetPosition(float newX, float newY) {
	x = newX;
	y = newY;
	boundingBox.x = newX;
	boundingBox.y = newY;
}

void Player::draw(int scrollX, int scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}