#ifndef RenderWindow_h
#define RenderWindow_h

#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <Windows.h>

#define brick_rows 8
#define brick_cols 6

using namespace std;

const float PI = 3.141592654;

const int window_w = 680;
const int window_h = 800;

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

class RenderWindow {
public:
	RenderWindow(const char* title, int posx, int posy, int w, int h);
	SDL_Texture* loadTexture(const char* path);
	void resetGame(Entity& paddle, Entity& ball, Entity bricks[]);
	void input(Entity& paddle, Entity& ball, Entity bricks[]);
	void update(Entity& paddle, Entity& ball, Entity bricks[]);
	void clear();
	void render(Entity& entity, float = 1.0, float = 1.0);
	void display();
	void clean();
	bool isRunning = false;
private:
	int count = 0;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;
	int fontSize=16;
	bool gameStarted = false;
};

#endif