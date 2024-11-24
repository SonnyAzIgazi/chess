#include "game.h"
#include "figure.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#include <algorithm>

Figure::Figure(Game* game, bool color) {
    this->game = game;
	this->color = color;
}

void King::render(SDL_Renderer* renderer, int x, int y) {
	Uint8 rgbColor;
	if (this->color) {
		rgbColor = 255;
	} else {
		rgbColor = 0;
	}
	SDL_SetRenderDrawColor(renderer, rgbColor, rgbColor, rgbColor, 255);
	SDL_Rect rect = {
		.x = x,
		.y = y,
		.w = FIGURE_SIZE,
		.h = FIGURE_SIZE
	};
	SDL_RenderFillRect(renderer, &rect);
}

/*
void Figure::move(int x, int y) {
	if (canMoveThere(x, y)) {
		Figure* onThatField = getFigureOnPosition(x, y);
		if (onThatField != nullptr) {
			figures.erase(std::remove(figures.begin(), figures.end(), onThatField), figures.end());
			delete onThatField;
		}
		this->rect->x = x * 60;
		this->rect->y = y * 60;
	}
}

bool Figure::canMoveThere(int x, int y) {
	if (this->figureType == FIGURE_TYPE_PAWN) {
		int ownX = this->rect->x/60;
		int ownY = this->rect->y/60;

		Figure* figureThere = getFigureOnPosition(x, y);
		if (figureThere != nullptr) {
			if (figureThere->color != this->color) {
				if (std::abs(ownX - x) == 1 && ownY + 1 == y) {
					return true;
				}
			}
		} else if (ownX == x && ownY + 1 == y) {
			return true;
		}
	} else {
		return true;
	}
	return false;
}
*/