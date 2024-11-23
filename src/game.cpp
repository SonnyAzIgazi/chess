#include "game.h"
#include "figure.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
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
		if (SDL_CreateWindowAndRenderer(WINDOW_SIZE+1, WINDOW_SIZE+1, 0, &window, &this->renderer) == 0) {
			SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

			this->board.resize(12, std::vector<Figure*>(12, nullptr));
			this->generateFigures();

			while (running) {
				this->Render();
				this->EventHandling();
			}
		}
		if (this->renderer) {
			SDL_DestroyRenderer(this->renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
}

void Game::Render() {
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	for (int x = 0; x <= 10; x++) {
		SDL_RenderDrawLine(this->renderer, x*WINDOW_SIZE/10, 0, x*WINDOW_SIZE/10, WINDOW_SIZE);
	}
	for (int y = 0; y <= 10; y++) {
		SDL_RenderDrawLine(this->renderer, 0, y*WINDOW_SIZE/10, WINDOW_SIZE, y*WINDOW_SIZE/10);
	}


	int counter = 0;

	for (int x = 0; x < 12; x++) {
		for (int y = 0; y < 12; y++) {
			if (this->board[x][y] != nullptr) {
				this->board[x][y]->render(this->renderer, x*60, y*60);
			}
		}
	}
		/*
		if (this->inHand == figure) {
			SDL_SetRenderDrawColor(this->renderer, figure->color, figure->color, figure->color, 100);
			SDL_RenderFillRect(this->renderer, figure->rect);

			int mX, mY;
			SDL_GetMouseState(&mX, &mY);

			SDL_SetRenderDrawColor(this->renderer, figure->color, figure->color, figure->color, 200);
			SDL_Rect rect = {
				.x = mX-30,
				.y = mY-30,
				.w = 60,
				.h = 60
			};
			SDL_RenderFillRect(this->renderer, &rect);

		} else {
			SDL_SetRenderDrawColor(this->renderer, figure->color, figure->color, figure->color, 255);
			SDL_RenderFillRect(this->renderer, figure->rect);
		}
		*/

	SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(this->renderer);
}

void Game::OnClick(SDL_Event* event) {
	int x = std::floor(event->button.x/60);
	int y = std::floor(event->button.y/60);


	/*
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
	*/
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
		this->board[x][2] = new King(this, true);
	}
}


void Game::KeyboardHandling(SDL_Event* event) {
	if (event->key.keysym.scancode == SDL_SCANCODE_Q)
		this->running = false;
	else if (event->key.keysym.scancode == SDL_SCANCODE_3)
		std::cout << "csa tesomsz" << std::endl;
}
