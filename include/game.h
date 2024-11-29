#pragma once
#include <SDL2/SDL.h>
#include <tuple>
#include <vector>

class Figure;

class Game {

public:
	int status = 0;

	Game();

	Figure* getFigureOnPosition(int x, int y);
	std::tuple<int, int> getFigureCoordinate(Figure* figure);
	SDL_Renderer* getRenderer();

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
