#pragma once
#include "Field.h"

class Tool : public Actor
{
public:
	Tool(std::string toolTexture, float x, float y, int height, int width);

	void update();
	virtual void processField(Field* field) = 0;

	std::string name;
	int lifeTime;

};

