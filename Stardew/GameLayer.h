#pragma once

#include <list>
#include "Layer.h"
#include "Player.h"
#include "Text.h"
#include "Crop.h"
#include "Tile.h"
#include "Space.h"
#include "Field.h"
#include "Background.h"
#include "Casa.h"
#include "SeedSeller.h"
#include "CropBuyer.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	Player* player;

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	Space* space;
	Background* background;

	//Mapa
	void loadMap(std::string name);
	void loadMapObject(char character, int x, int y);
	void calculateScroll();
	float scrollX = 0;
	int mapWidth = 0;
	float scrollY = 0;
	int mapHeight = 0;
	std::list<Tile*> tiles;

	//Cultivos (projectiles)
	std::list<Crop*> seeds;
	std::list<Crop*> crops;

	//Herramientas (projectiles)
	std::list<Tool*> tools;

	//Campo
	std::list<Field*> fields;

	//Casa
	Casa* casa;

	//NPCs
	SeedSeller* seedSeller;
	CropBuyer* cropBuyer;

	//Controles
	bool controlWork = false;
	bool controlAction = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	//Dinero
	Actor* backgroundMoney;
	Text* textMoney;

	//Energía
	Actor* backgroundEnergy;
	Text* textEnergy;

	//Tiempo
	int nextDayCounter = 50; // para que no pasen varios días seguidos al entrar en la casa
	int dayTime = 1000;
	int currentDay = 1;
	void startNextDay();
	Text* textDay;

	//Inventario
	Actor* backgroundInventory[9];
	Actor* backgroundInv1;
	Actor* backgroundInv2;
	Actor* backgroundInv3;
	Actor* backgroundInv4;
	Actor* backgroundInv5;
	Actor* backgroundInv6;
	Actor* backgroundInv7;
	Actor* backgroundInv8;
	Actor* backgroundInv9;
	void updateInventory();
};

