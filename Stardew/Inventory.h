#pragma once
#include"InvItem.h"

class Inventory
{
public:
	Inventory();

	InvItem* inventory[9];
	InvItem* selectedItem;
	int size;

	void select(int index);
	bool isFull();
	void add(InvItem* item);
	InvItem* getItemAt(int index);
	int sellCrops();

};

