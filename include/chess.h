#pragma once
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#define FIGURE_TYPE_PAWN 0
#define FIGURE_TYPE_BISHOP 1
#define FIGURE_TYPE_KNIGHT 2
#define FIGURE_TYPE_ROOK 3
#define FIGURE_TYPE_QUEEN 4
#define FIGURE_TYPE_KING 5

class Figure {
	public:
		SDL_Rect* rect;
		SDL_Texture* texture;
		char figureType;
		Uint8 color;

		static std::vector<Figure*> figures;
		static Figure* getFigureOnPosition(int x, int y);

		Figure(int x, int y, char figureType, Uint8 color);
		void move(int x, int y);
		bool canMoveThere(int x, int y);
};