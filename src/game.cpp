#include "game.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#define WINDOW_SIZE 600

Game::Game() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		if (SDL_CreateWindowAndRenderer(WINDOW_SIZE+1, WINDOW_SIZE+1, 0, &window, &renderer) == 0) {
			 SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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

	for (auto &figure : Figure::figures) {
		if (inHand == figure) {
			SDL_SetRenderDrawColor(renderer, figure->color, figure->color, figure->color, 100);
			SDL_RenderFillRect(renderer, figure->rect);

			int mX, mY;
			SDL_GetMouseState(&mX, &mY);

			SDL_SetRenderDrawColor(renderer, figure->color, figure->color, figure->color, 200);
			SDL_Rect rect = {
				.x = mX-30,
				.y = mY-30,
				.w = 60,
				.h = 60
			};
			SDL_RenderFillRect(renderer, &rect);

		} else {
			SDL_SetRenderDrawColor(renderer, figure->color, figure->color, figure->color, 255);
			SDL_RenderFillRect(renderer, figure->rect);
		}
	}
	
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
}

void Game::OnClick(SDL_Event* event) {
	int x = std::floor(event->button.x/60);
	int y = std::floor(event->button.y/60);

	

	if (event->button.button == SDL_BUTTON_LEFT) {
		if (event->button.state == SDL_PRESSED) {
			Figure* figureThere = Figure::getFigureOnPosition(x, y);

			if (figureThere != nullptr) {
				inHand = figureThere;
			}
		} else {
			if (inHand != nullptr) {
				inHand->move(x, y);
				inHand = nullptr;
			}
		}
		
	}
}

void Game::EventHandling() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			KeyboardHandling(&event);
		} else if (event.type == SDL_QUIT) {
			this->running = false;
		} else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			OnClick(&event);
		}
	}
}

void Game::generateFigures() {
	for (int x = 0; x < 10; x++) {
		Figure* newFigure = new Figure(x, 2, FIGURE_TYPE_KING, 255);
		Figure::figures.push_back(newFigure);
	}
}


void Game::KeyboardHandling(SDL_Event* event) {
	if (event->key.keysym.scancode == SDL_SCANCODE_Q)
		this->running = false;
	else if (event->key.keysym.scancode == SDL_SCANCODE_3)
		std::cout << "csa tesomsz" << std::endl;
}
