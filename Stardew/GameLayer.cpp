#include "GameLayer.h"
#include "Game.h"
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>

GameLayer::GameLayer() : Layer() {
	init();
}

void GameLayer::init() {
	//Físicas
	space = new Space();

	background = new Background("res/fondo_2.png", WIDTH * 0.5,
		HEIGHT * 0.5);

	//Player
	player = new Player(WIDTH * .15f, HEIGHT * .55f);
	player->y -= player->height / 2;
	player->boundingBox.update(player->x, player->y);
	space->addDynamicActor(player);

	//Dinero
	textMoney = new Text("0", WIDTH * .92f, HEIGHT * .05f);
	backgroundMoney = new Actor("res/moneda.png",
		WIDTH * .85f, HEIGHT * .06f, 40, 40);

	//Energía
	textEnergy = new Text("100", WIDTH * 0.94f, HEIGHT * .94f);
	backgroundEnergy = new Actor("res/energia.png",
		WIDTH * .85f, HEIGHT * .94f, 40, 40);

	//Tiempo
	textDay = new Text("Día " + std::to_string(currentDay), WIDTH * .70f, HEIGHT * .05f);

	//Casa
	casa = new Casa(WIDTH * .167, HEIGHT * .375);
	casa->y -= casa->height / 2;
	casa->boundingBox.update(casa->x, casa->y);
	space->addStaticActor(casa);

	//Vendedor semillas
	seedSeller = new SeedSeller(WIDTH * .865, HEIGHT * .5);
	seedSeller->y -= seedSeller->height / 2;
	seedSeller->boundingBox.update(seedSeller->x, seedSeller->y);
	space->addDynamicActor(seedSeller);

	//Comprador cultivos
	cropBuyer = new CropBuyer(WIDTH * .865, HEIGHT * .35);
	cropBuyer->y -= cropBuyer->height / 2;
	cropBuyer->boundingBox.update(cropBuyer->x, cropBuyer->y);
	space->addDynamicActor(cropBuyer);

	tiles.clear();
	fields.clear();
	tools.clear();

	loadMap("res/0.txt");
}

void GameLayer::processControls() {
	Layer::processControls();
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}

	if (controlWork) {
		if (player->isSelectedTool()) {
			Tool* newTool = player->useTool();
			if (newTool != nullptr) {
				tools.push_back(newTool);
				space->addDynamicActor(newTool);
			}
		}
		else if (player->isSelectedSeed()) {
			Crop* newCrop = player->useSeed();
			if (newCrop != nullptr) {
				seeds.push_back(newCrop);
				space->addDynamicActor(newCrop);
			}
		}
	}
	if (controlAction) {
		if (player->isOverlapping(cropBuyer)) {
			player->sellCrops();
		}
		else if (player->isOverlapping(seedSeller)) {

		}
		else if (player->isEntering(casa)) {
			startNextDay();
			player->energy = 100;
		}
	}

	player->moveX(controlMoveX);
	player->moveY(controlMoveY);
}

void GameLayer::keysToControls(SDL_Event event) {
	Layer::keysToControls(event);
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			Game::getInstance().loopActive = false;
			break;
		case SDLK_x:
			Game::getInstance().scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_1:
			player->selectFromInventory(0);
			break;
		case SDLK_2:
			player->selectFromInventory(1);
			break;
		case SDLK_3:
			player->selectFromInventory(2);
			break;
		case SDLK_4:
			player->selectFromInventory(3);
			break;
		case SDLK_5:
			player->selectFromInventory(4);
			break;
		case SDLK_6:
			player->selectFromInventory(5);
			break;
		case SDLK_7:
			player->selectFromInventory(6);
			break;
		case SDLK_8:
			player->selectFromInventory(7);
			break;
		case SDLK_9:
			player->selectFromInventory(8);
			break;
		case SDLK_SPACE: // usar herramienta/item
			if(player->hasEnergy())
				controlWork = true;
			break;
		case SDLK_e: // hablar con npc
			controlAction = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE:
			controlWork = false;
			break;
		case SDLK_e:
			controlAction = false;
			break;
		}
	}
}

void GameLayer::update() {
	std::unordered_set<Tool*> deleteTools;
	std::unordered_set<Crop*> deleteSeeds;
	std::unordered_set<Crop*> deleteCrops;

	space->update();
	player->update();
	seedSeller->update();
	cropBuyer->update();

	//Herramientas
	for (auto const& tool : tools) {
		tool->update();
		if (tool->lifeTime == 0) {
			deleteTools.emplace(tool);
		}
	}

	//Cultivos (semillas)
	for (auto const& seed : seeds) {
		seed->update();
		if (seed->seedLifeTime == 0) {
			deleteSeeds.emplace(seed);
		}
	}

	//Cultivos (plantados)
	for (auto const& crop : crops) {
		if (crop->state == CropState::Croppped) {
			deleteCrops.emplace(crop);
		}
	}

	//Energia
	textEnergy->content = std::to_string(player->energy);

	//Dinero
	textMoney->content = std::to_string(player->money);

	//Usar herramientas
	for (auto const& tool : tools) {
		for (auto const& field : fields) {
			if (field->containsPoint(tool->x, tool->y)) {
				tool->processField(field);
			}
		}
	}

	//Usar semillas
	for (auto const& seed : seeds) {
		for (auto const& field : fields) {
			if (field->canBePlanted() && field->containsPoint(seed->x, seed->y)) {
				seed->plant(field);
				crops.emplace_back(seed);
			}
		}
	}

	//Inventario
	updateInventory();

	//Delete
	for (auto const& delTool : deleteTools) {
		tools.remove(delTool);
		space->removeDynamicActor(delTool);
	}
	deleteTools.clear();

	for (auto const& delSeed : deleteSeeds) {
		seeds.remove(delSeed);
		space->removeDynamicActor(delSeed);
	}
	deleteSeeds.clear();

	for (auto const& delCrop : deleteCrops) {
		crops.remove(delCrop);
		space->removeDynamicActor(delCrop);
	}
	deleteCrops.clear();

	//Día
	dayTime--;

	if (nextDayCounter > 0) {
		nextDayCounter--;
	}

	if (dayTime == 0) {
		startNextDay();
	}
}

void GameLayer::updateInventory() {
	float incX = 0;
	float x = WIDTH * (.15f + incX);
	float y = HEIGHT * .95f;
	std::string texture;
	for (int i = 0; i < 9; i++) {
		InvItem* item = player->getFromInventory(i);
		if (item->type == "seed")
			texture = "res/" + item->name + "_" + item->type + "s.png";
		else
			texture = "res/" + item->name + "_" + item->type + ".png";
		backgroundInventory[i] = new Actor(texture, x, y, 32, 32);
		incX += .07f;
		x = WIDTH * (.15f + incX);
	}
}

void GameLayer::startNextDay() {
	if (nextDayCounter == 0){
		nextDayCounter = 50;
		dayTime = 1000;
		currentDay++;

		for (auto const& field : fields) {
			field->nextDay();
		}

		textDay->content = "Día " + std::to_string(currentDay);

		player->resetPosition();
	}
}

void GameLayer::draw() {
	calculateScroll();

	background->draw();

	//Campo
	for (auto const& field : fields) {
		field->draw(scrollX, scrollY);
	}

	//Tiles
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	//Herramientas
	for (auto const& tool : tools) {
		tool->draw(scrollX, scrollY);
	}

	//Semillas
	for (auto const& seed : seeds) {
		seed->draw(scrollX, scrollY);
	}

	//Cultivos
	for (auto const& crop : crops) {
		crop->draw(scrollX, scrollY);
	}

	//NPCs
	seedSeller->draw(scrollX, scrollY);
	cropBuyer->draw(scrollX, scrollY);

	//Player
	player->draw(scrollX, scrollY);

	//Dinero
	backgroundMoney->draw();
	textMoney->draw();

	//Energia
	backgroundEnergy->draw();
	textEnergy->draw();

	//Tiempo
	textDay->draw();

	//Casa
	casa->draw(scrollX, scrollY);

	//Inventario
	for (auto const& slot : backgroundInventory) {
		slot->draw();
	}

	SDL_RenderPresent(Game::getRenderer());
}

void GameLayer::loadMap(std::string name) {
	std::ifstream file(name);
	int row = 0;
	std::string line;

	while (std::getline(file, line)) {
		mapWidth = line.size();
		for (int column = 0; column < line.size(); column++) {
			int x = 40 / 2 + column * 40;
			int y = 40 + row * 40;
			loadMapObject(line[column], x, y);
			std::cout << line[column];
		}
		std::cout << std::endl;
		row++;
	}
}

void GameLayer::loadMapObject(char character, int x, int y) {
	switch (character)
	{
	case '#': {	//bloques que limitan el mapa
		Tile* tile = new Tile("res/piedra.png", x, y);
		tile->y -= tile->height / 2;
		tile->boundingBox.update(tile->x, tile->y);
		tiles.emplace_back(tile);
		space->addStaticActor(tile);
	}
	case '.': {	//hierba
		Field* field = new Field("res/hierba.png", x, y);
		field->y -= field->height / 2;
		field->boundingBox.update(field->x, field->y);
		fields.emplace_back(field);
		space->addDynamicActor(field);
	}
	
	}
}

void GameLayer::calculateScroll() {
	if (player->x > WIDTH * 0.3f || player->x < mapWidth - WIDTH * .3f) {

		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}

	if (player->y > HEIGHT * 0.4f || player->y < mapHeight - HEIGHT * .4f) {

		if (player->y - scrollY < HEIGHT * 0.4) {
			scrollY = player->y - HEIGHT * 0.4;
		}
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
}
