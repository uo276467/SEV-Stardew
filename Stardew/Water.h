#pragma once
#include "Tool.h"

class Water : public Tool
{
public:
	Water(float x, float y, int height, int width);

	void processField(Field* field) override;
};

