#pragma once
#include <string>

class InvItem
{
public:
	InvItem(std::string name, std::string type, int value);
	InvItem(std::string name, std::string type, int units, int value);

	std::string name;
	std::string type;
	int units;
	int value;

	void incUnits();
	void decUnits();
	int calculateValue();
	void empty();
};

