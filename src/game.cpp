#include "game.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#define WINDOW_SIZE 600

Game::Game() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		if (SDL_CreateWindowAndRenderer(WINDOW_SIZE+8, WINDOW_SIZE+8, 0, &window, &renderer) == 0) {
			generateFigures();

			while (running) {
				this->Render();
				this->EventHandling();
			}
		}
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int x = 0; x <= 10; x++) {
		SDL_RenderDrawLine(renderer, x*WINDOW_SIZE/10, 0, x*WINDOW_SIZE/10, WINDOW_SIZE);
	}
	for (int y = 0; y <= 10; y++) {
		SDL_RenderDrawLine(renderer, 0, y*WINDOW_SIZE/10, WINDOW_SIZE, y*WINDOW_SIZE/10);
	}
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
}

void Game::EventHandling() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			KeyboardHandling(&event);
		} else if (event.type == SDL_QUIT) {
			this->running = false;
		}
	}
}

void Game::generateFigures() {
	for (int x = 0; x < 10; x++) {
		Figure* newFigure = new Figure(x, 0, FIGURE_TYPE_PAWN, 255);
		Figure::figures.push_back(newFigure);
	}
}


void Game::KeyboardHandling(SDL_Event* event) {
	if (event->key.keysym.scancode == SDL_SCANCODE_Q)
		this->running = false;
	else if (event->key.keysym.scancode == SDL_SCANCODE_3)
		std::cout << "csa tesomsz" << std::endl;
}
