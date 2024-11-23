#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
//#include <SDL2/SDL_scancode.h>
#include <vector>

class Figure;

class Game {

public:
	int status = 0;

	Game();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running = true;

	std::vector<std::vector<Figure*>> board;
	Figure* inHand = nullptr;

	void Render();

	void EventHandling();
	void KeyboardHandling(SDL_Event* event);
	void OnClick(SDL_Event* event);

	void generateFigures();
};