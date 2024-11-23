#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <game.h>

int main() {
	Game* game = new Game();
	std::cout << game->status << std::endl;
	
	return 0;
}
