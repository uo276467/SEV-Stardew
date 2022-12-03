#pragma once

#include <SDL.h>

enum class InputType {
	Keyboard,
	Mouse,
	Gamepad
};

class Layer
{
public:
	Layer();

	virtual void init() = 0;
	virtual void processControls();
	virtual void update() {};
	virtual void draw() = 0;
	//virtual hace que los métodos se puedan implementar por otras clases
	//el = 0 indica que los métodos están implementados en otra clase 

protected:
	virtual void keysToControls(SDL_Event event);
	virtual void mouseToControls(SDL_Event event);
	virtual void gamepadToControls(SDL_Event event);

	bool getButton(SDL_GameControllerButton button);
	int getAxis(SDL_GameControllerAxis axis);

	InputType inputType = InputType::Keyboard;

private:
	SDL_GameController* gamepad;
};


