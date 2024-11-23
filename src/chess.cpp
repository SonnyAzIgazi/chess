#include "chess.h"
#include <vector>
#include <math.h>
#include <algorithm>



Figure::Figure(int x, int y, char figureType, Uint8 color) {
	this->rect = new SDL_Rect;
	this->rect->x = x * 60;
	this->rect->y = y * 60;
	this->rect->h = 60;
	this->rect->w = 60;

	this->figureType = figureType;
	this->color = color;
}

std::vector<Figure* > Figure::figures;

Figure* Figure::getFigureOnPosition(int x, int y) {
	for (auto &figure : figures) {
		if (figure->rect->x/60 == x && figure->rect->y/60 == y) {
			return figure;
		}
	}
	return nullptr;
}

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
