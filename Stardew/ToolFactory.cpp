#include "ToolFactory.h"
#include "Hoe.h"
#include "Water.h"
#include "Gloves.h"
#include "Player.h"

ToolFactory::ToolFactory() {

}

Tool* ToolFactory::createTool(InvItem* invItem, float x, float y, Player* player) {
	std::string name = invItem->name;
	if (name == "hoe") {
		Hoe* hoe = new Hoe(x, y, 18, 6);
		return hoe;
	}
	else if (name == "water") {
		Water* water = new Water(x, y, 28, 28);
		return water;
	}
	else if (name == "gloves") {
		Gloves* gloves = new Gloves(x, y, 20, 20, player);
		return gloves;
	}
	return nullptr;
}
