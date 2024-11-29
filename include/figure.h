#pragma once
#include <SDL2/SDL.h>

class Game;

class Figure {
	public:
        Figure(Game* game, bool color);
        virtual ~Figure() {};

        virtual bool canMove(int currentX, int currentY, int nextX, int nextY);

        void init();

        SDL_Texture* getTexture();
    protected:
        Game* game;
		bool color;
		SDL_Texture* texture;

		virtual void renderTexture() = 0;

    private:
};

class King : public Figure {
    public:
        King(Game* game, bool color)
            : Figure(game, color) {}

        void renderTexture() override;
};
