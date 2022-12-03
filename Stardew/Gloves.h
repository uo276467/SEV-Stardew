#pragma once
#include "Tool.h"
class Player;

class Gloves : public Tool
{
public:
	Gloves(float x, float y, int height, int width, Player* player);

	void processField(Field* field) override;

	Player* player;
};

