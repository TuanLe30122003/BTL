#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "header.h"
#include "snake.h"

using namespace std;


int main(int argc, char* argv[])
{
    // Init game window
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_RenderClear(renderer);

	SDL_Event e;

	bool running = true;
	snake snake = {};

	position random = randomLocation();

	snake.snakePos.x = random.x;
	snake.snakePos.y = random.y;

	food food = {};
	food.foodCreation();

	int currentTime = 0, previousTime, time;

	// demo
   TTF_Font* font = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

	font = TTF_OpenFont("VeraMoBd.ttf", 30);

	SDL_Color fg = { 243, 156, 18 };

	string text = "WELCOME";
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = 0;
	srcRest.y =  0;

	desRect.x = 200;
	desRect.y = 270;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;

	//end demo

	SDL_Texture* background = loadTexture("background4.png",renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);

	while (running) {
		previousTime = currentTime;
		currentTime = SDL_GetTicks(); // lấy số mili giây từ lúc chương trình được cài đặt
		time = currentTime - previousTime;
		int frames = 0;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w: if (snake.presentDir.y != 1) snake.changeDir = { 0, -1 }; break;
				case SDLK_s: if (snake.presentDir.y != -1) snake.changeDir = { 0, 1 }; break;
				case SDLK_a: if (snake.presentDir.x != 1) snake.changeDir = { -1, 0 }; break;
				case SDLK_d: if (snake.presentDir.x != -1) snake.changeDir = { 1, 0 }; break;
				}
			}
		}

		snake.update(time, food);
        if(snake.insideCheck() == false || snake.self_killedCheck() == true) running = false;

        SDL_Texture* background = loadTexture("background4.png",renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        //SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &srcRest, &desRect);

		snake.draw(renderer);
		food.draw(renderer);

        SDL_RenderPresent(renderer);
	}

    quitSDL(window, renderer);

	return 0;
}
