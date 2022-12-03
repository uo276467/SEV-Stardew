#pragma once
#include "Tool.h"
#include "InvItem.h"
class Player;

class ToolFactory
{
public:
	ToolFactory();

	Tool* createTool(InvItem* invItem, float x, float y, Player* player);
};

