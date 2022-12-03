#include "Tool.h"

Tool::Tool(std::string toolType, float x, float y, int height, int width)
	: Actor(toolType, x, y, height, width) {
	lifeTime = 20;
	vx = 0;
}

void Tool::update() {
	if (lifeTime > 0) {
		lifeTime--;
	}
}