#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include "chess.h"
#include <vector>

class Game {

public:
	int status = 0;

	Game();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running = true;

	void Render();
	void EventHandling();
	void KeyboardHandling(SDL_Event* event);
	void generateFigures();
};