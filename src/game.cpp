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

Game::Game() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		if (SDL_CreateWindowAndRenderer(900, 900, 0, &window, &this->renderer) == 0) {
			SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

			this->board.resize(12, std::vector<Figure*>(12, nullptr));
			this->generateFigures();

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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

	this->renderMap();

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

void Game::renderMap() {
    SDL_Rect rect;
    rect.w = FIGURE_SIZE;
    rect.h = FIGURE_SIZE;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            rect.x = x * FIGURE_SIZE;
            rect.y = y * FIGURE_SIZE;
            if ((x+y) % 2 == 0) {
                SDL_SetRenderDrawColor(this->renderer, 190, 190, 100, SDL_ALPHA_OPAQUE);
            } else {
                SDL_SetRenderDrawColor(this->renderer, 240, 240, 206, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderFillRect(this->renderer, &rect);
        }
    }
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
				if (std::get<0>(coords) == x && std::get<1>(coords) == y) {
				    inHand = nullptr;
				    return;
				}
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
	for (int x = 0; x < BOARD_SIZE; x++) {
		this->board[x][BOARD_SIZE-2] = new Pawn(this, true);
		this->board[x][BOARD_SIZE-2]->init();
	}
}


void Game::KeyboardHandling(SDL_Event* event) {
	if (event->key.keysym.scancode == SDL_SCANCODE_Q)
		this->running = false;
	else if (event->key.keysym.scancode == SDL_SCANCODE_3)
		std::cout << "csa tesomsz" << std::endl;
}
