#include "Inventory.h"
#include <iostream>;

Inventory::Inventory() {
	inventory[0] = new InvItem("hoe", "tool", 1, 0);
	inventory[1] = new InvItem("water", "tool", 1, 0);
	inventory[2] = new InvItem("gloves", "tool", 1, 0);
	inventory[3] = new InvItem("pepper", "seed", 10, 0);
	inventory[4] = new InvItem("empty", "slot", 0, 0);
	inventory[5] = new InvItem("empty", "slot", 0, 0);
	inventory[6] = new InvItem("empty", "slot", 0, 0);
	inventory[7] = new InvItem("empty", "slot", 0, 0);
	inventory[8] = new InvItem("empty", "slot", 0, 0);
	selectedItem = inventory[0];
	size = 4;
}

void Inventory::select(int index) {
	selectedItem = inventory[index];
}

bool Inventory::isFull() {
	return size == 9;
}

void Inventory::add(InvItem* item) {
	for (int i = 0; i < 9; i++) {
		if (inventory[i]->name == item->name && inventory[i]->type == item->type) {
			inventory[i]->incUnits();
			return;
		}
	}

	for (int i = 0; i < 9; i++) {
		if (inventory[i]->name == "empty") {
			inventory[i] = item;
			size++;
			return;
		}
	}
}

InvItem* Inventory::getItemAt(int index) {
	return inventory[index];
}

int Inventory::sellCrops() {
	int money = 0;
	for (int i = 0; i < 9; i++) {
		if (inventory[i]->type == "crop") {
			money += inventory[i]->calculateValue();
			inventory[i]->empty();
			size--;
		}
	}
	return money;
}
