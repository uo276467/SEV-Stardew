#pragma once
#include "Hoe.h"
#include "Water.h"
#include "Gloves.h"
#include "Animation.h"
#include "Game.h"
#include "Casa.h"
#include "Inventory.h"
#include "CropFactory.h"
#include "ToolFactory.h"

class Player : public Actor
{
public:
	Player(float x, float y);

	void update();
	void draw(int scrollX = 0, int scrollY = 0) override;
	void moveX(float direction);
	void moveY(float direction);
	void resetPosition(float newX, float newY);

	int actionTime = 20;
	int actionCadence = 20;

	//Dinero
	int money = 0;

	//Factorias
	ToolFactory* toolFactory = new ToolFactory();
	CropFactory* cropFactory = new CropFactory();

	//Inventario
	Inventory* inventory;
	bool isSelectedTool();
	bool isSelectedSeed();
	void selectFromInventory(int index);
	void addToInventory(InvItem* item);
	InvItem* selectedItem();
	InvItem* getFromInventory(int index);
	Tool* useTool();
	Crop* useSeed();

	//Herramientas
	Hoe* hoe;
	Water* water;
	Gloves* gloves;

	//Energía
	int energy = 100;
	bool hasEnergy();

	//Entrar a casa
	bool isEntering(Casa* casa);

	//Vender cultivos
	int sellCrops();

	Animation* animation;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aShootingRight;
	Animation* aShootingLeft;

	State state = State::Moving;
	Orientation orientation = Orientation::Right;

};

