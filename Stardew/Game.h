#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "Layer.h"

#define WIDTH 480
#define HEIGHT 320

enum class State {
	Moving,
	DoingAction
};

enum class Orientation {
	Left,
	Right
};

class Game
{
public:
	Game();

	static Game& getInstance(); //Singleton

	static SDL_Renderer* getRenderer() {
		return getInstance().renderer;
	}

	static TTF_Font* getFont() {
		return getInstance().font;
	}

	static SDL_Texture* getTexture(std::string filename) {
		static std::unordered_map<std::string, SDL_Texture*> textures;

		if (textures.find(filename) == textures.end()) {
			SDL_Surface* surface = IMG_Load(filename.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(
				getRenderer(), surface);

			SDL_FreeSurface(surface);
			textures[filename] = texture;
		}
		return textures[filename];
	}

	void start();
	void scale();
	bool scaledToMax = false;
	float scaleLower = 1.f; //o 1.0f

	void loop();

	bool loopActive = true;
	Layer* layer;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
};
