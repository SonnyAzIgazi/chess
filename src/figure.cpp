#include "game.h"
#include "figure.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <math.h>

Figure::Figure(Game* game, bool color) {
    this->game = game;
	this->color = color;
}

void Figure::init() {
	this->renderTexture();
}

SDL_Texture* Figure::getTexture() {
	return this->texture;
}

bool Figure::canMove(int currentX, int currentY, int nextX, int nextY) {
	return true;
}

void King::renderTexture() {
	SDL_Renderer* renderer = this->game->getRenderer();
	bool boolArray[8][8] = {
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1}
    };

    Uint32 pixels[8][8];
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (boolArray[x][y]) {
                pixels[x][y] = 0xFFFFFFAA; // White pixel (RGBA: 255, 255, 255, 255)
            } else {
                pixels[x][y] = 0x000000AA; // Black pixel (RGBA: 0, 0, 0, 255)
            }
        }
    }

	this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 8, 8);
    SDL_UpdateTexture(this->texture, nullptr, pixels, 8 * sizeof(Uint32));
}
