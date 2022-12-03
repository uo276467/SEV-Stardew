#pragma once
#include "Tool.h"
class Hoe : public Tool //azada
{
public:
	Hoe(float x, float y, int height, int width);

	void processField(Field* field) override;
};

