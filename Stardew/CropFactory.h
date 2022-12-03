#pragma once
#include "Crop.h"
#include "InvItem.h"
class CropFactory
{
public:
	CropFactory();
	Crop* createCrop(InvItem* invItem, float x, float y);
};

