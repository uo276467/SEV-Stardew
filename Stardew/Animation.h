#pragma once
#include "SDL.h"
#include <string>

class Animation
{
public:
	Animation(std::string filename, int actorWidth, int actorHeight,
		int fileWidth, int fileHeight, int updateFrequency,
		int totalFrames, bool loop = false);

	bool update();
	void draw(float x, float y);

	int actorWidth, actorHeight, fileWidth, fileHeight, frameWidth, frameHeight;
	int totalFrames, currentFrame = 0;
	int updateFrequency, updateTime = 0;
	bool loop;

	SDL_Texture* texture;
	SDL_Rect source;
};

