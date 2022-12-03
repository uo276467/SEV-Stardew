#include "Game.h"
#include "GameLayer.h"

constexpr int FRAME_TIME = 1000 / 30;

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error SDL_Init"
			<< SDL_GetError()
			<< std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		std::cout << "Error Window y Renderer"
			<< SDL_GetError()
			<< std::endl;
	}
	SDL_SetWindowTitle(window, "Stardew");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	TTF_Init();
	font = TTF_OpenFont("res/sans.ttf", 24);
}

Game& Game::getInstance() {		//& devuelve una referencia
	static Game instance;
	return instance;
}

void Game::loop() {
	int initTick, endTick, deltaTick;
	while (loopActive) {
		initTick = SDL_GetTicks();
		//Input
		layer->processControls();
		//Update
		layer->update();
		//Render
		layer->draw();
		//Esperamos

		endTick = SDL_GetTicks();
		deltaTick = endTick - initTick;

		if (deltaTick < FRAME_TIME) {
			SDL_Delay(FRAME_TIME - deltaTick);
		}
	}
}

void Game::start() {
	layer = new GameLayer();
	loopActive = true; // bucle activo
	loop();
}

void Game::scale() {
	scaledToMax = !scaledToMax;
	if (scaledToMax) {
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = (float)PCdisplay.w / (float)WIDTH;
		float scaleY = (float)PCdisplay.h / (float)HEIGHT;
		// Necesitamos la menor de las 2 escalas para no deformar el juego
		scaleLower = scaleX;
		if (scaleY < scaleX) {
			scaleLower = scaleY;
		}
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, WIDTH * scaleLower, HEIGHT * scaleLower);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, scaleLower, scaleLower);
	}
	else { // Escala Original
		scaleLower = 1;
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, 1, 1);
	}

}
