#include "game.h"
#include "figure.h"
#include "globals.h"
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

SDL_Renderer* Game::getRenderer() {
	return this->renderer;
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

	int mX, mY;
	SDL_GetMouseState(&mX, &mY);

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (this->board[x][y] != nullptr) {
				SDL_Rect rect;
				rect.w = FIGURE_SIZE;
				rect.h = FIGURE_SIZE;
				if (this->board[x][y] == this->inHand) {
					rect.x = mX - FIGURE_SIZE / 2;
					rect.y = mY - FIGURE_SIZE / 2;
				} else {
					rect.x = x * FIGURE_SIZE;
					rect.y = y * FIGURE_SIZE;
				}
				SDL_RenderCopy(this->renderer, this->board[x][y]->getTexture(), nullptr, &rect);
			}
		}
	}

	SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(this->renderer);
}

Figure* Game::getFigureOnPosition(int x, int y) {
	if (x >= BOARD_SIZE || x < 0 || y >= BOARD_SIZE || y < 0) {
		return nullptr;
	}

	return this->board[x][y];
}

std::tuple<int, int> Game::getFigureCoordinate(Figure* figure) {
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (this->board[x][y] == figure) {
				return {x, y};
			}
		}
	}
}

void Game::OnClick(SDL_Event* event) {
	int x = std::floor(event->button.x/60);
	int y = std::floor(event->button.y/60);


	if (event->button.button == SDL_BUTTON_LEFT) {
		if (event->button.state == SDL_PRESSED) {
			Figure* clickedFigure = this->board[x][y];

			if (clickedFigure != nullptr) {
				inHand = clickedFigure;
			}
		} else {
			if (inHand != nullptr) {
				std::tuple<int, int> coords = this->getFigureCoordinate(inHand);
				if (inHand->canMove(std::get<0>(coords), std::get<1>(coords), x, y)) {
					this->board[x][y] = this->board[std::get<0>(coords)][std::get<1>(coords)];
					this->board[std::get<0>(coords)][std::get<1>(coords)] = nullptr;
				}
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
		this->board[x][2] = new King(this, true);
		this->board[x][2]->init();
	}
}


void Game::KeyboardHandling(SDL_Event* event) {
	if (event->key.keysym.scancode == SDL_SCANCODE_Q)
		this->running = false;
	else if (event->key.keysym.scancode == SDL_SCANCODE_3)
		std::cout << "csa tesomsz" << std::endl;
}
