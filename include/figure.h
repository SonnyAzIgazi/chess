#pragma once
//#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL.h>
#include <vector>

class Game;

class Figure {
	public:
        Figure(Game* game, bool color);
        virtual ~Figure() {};

		//void move(int x, int y);
		//virtual bool isValidMove(int x, int y);
        virtual void render(SDL_Renderer* renderer, int x, int y) = 0;
    protected:
        Game* game;
		bool color;

    private:
};

class King : public Figure {
    public:
        King(Game* game, bool color)
            : Figure(game, color) {}

        void render(SDL_Renderer* renderer, int x, int y) override;
};