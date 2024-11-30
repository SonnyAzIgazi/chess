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
	bool icon[10][10] = {
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}
	};

    Uint32 pixels[10][10];
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (icon[x][y]) {
            	pixels[x][y] = this->color ? 0xAAAAAAFF : 0x222222FF; // White pixel (RGBA: 255, 255, 255, 255)
            } else {
                pixels[x][y] = 0x00000000; // Black pixel (RGBA: 0, 0, 0, 255)
            }
        }
    }

	this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 10, 10);
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(this->texture, nullptr, pixels, 10 * sizeof(Uint32));
}

void Pawn::renderTexture() {
	SDL_Renderer* renderer = this->game->getRenderer();
	bool icon[10][10] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 0}
	};

    Uint32 pixels[10][10];
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            if (icon[x][y]) {
                pixels[x][y] = this->color ? 0xDDDDDDFF : 0x222222FF; // White pixel (RGBA: 255, 255, 255, 255)
            } else {
                pixels[x][y] = 0x00000000; // Black pixel (RGBA: 0, 0, 0, 255)
            }
        }
    }

	this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 10, 10);
	SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(this->texture, nullptr, pixels, 10 * sizeof(Uint32));
}
