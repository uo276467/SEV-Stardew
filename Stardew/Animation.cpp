#include "Animation.h"
#include "Game.h" 

Animation::Animation(std::string filename, int actorWidth, int actorHeight,
	int fileWidth, int fileHeight,
	int updateFrequency, int totalFrames,
	bool loop)
	: actorWidth(actorWidth), actorHeight(actorHeight),
	fileWidth(fileWidth), fileHeight(fileHeight),
	updateFrequency(updateFrequency), totalFrames(totalFrames),
	frameWidth(fileWidth / totalFrames), frameHeight(fileHeight),
	loop(loop)
{
	texture = Game::getTexture(filename);
	source = { 0, 0, frameWidth, frameHeight };
}

bool Animation::update() {
	updateTime++;

	if (updateTime > updateFrequency) { //hemos esperado lo suficiente para mover al siguiente frame
		updateTime = 0;
		currentFrame = (currentFrame + 1) % totalFrames;
		if (currentFrame == 0 && !loop) {
			return true;	//la animaci�n se ha terminado (para que no se quede congelado en el final de la animaci�n
		}
	}

	source.x = currentFrame * frameWidth; //actualizar posici�n
	return false;
}

void Animation::draw(float x, float y) {
	SDL_Rect destination{ x - actorWidth / 2, y - actorHeight / 2,
		actorWidth, actorHeight };
	SDL_RenderCopyEx(Game::getRenderer(), texture, &source, &destination,
		0, NULL, SDL_FLIP_NONE);
}
