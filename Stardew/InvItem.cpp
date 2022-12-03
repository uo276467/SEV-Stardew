#include "InvItem.h"
#include <iostream>

InvItem::InvItem(std::string name, std::string type, int value)
	: name(name), type(type), value(value) {
	units = 1;
}

InvItem::InvItem(std::string name, std::string type, int units, int value)
	: name(name), type(type), units(units), value(value) {
}

void InvItem::incUnits() {
	units++;
}

void InvItem::decUnits() {
	if (units > 0) {
		units--;
	}
	if (units == 0) {
		empty();
	}
}

int InvItem::calculateValue() {
	return value * units;
}

void InvItem::empty() {
	name = "empty";
	type = "slot";
	units = 0;
	value = 0;
}