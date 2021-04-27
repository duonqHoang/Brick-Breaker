#ifndef RenderWindow_h
#define RenderWindow_h

#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cmath>

using namespace std;

const float PI = 3.141592654;

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

class RenderWindow {
public:
	RenderWindow(const char* title, int posx, int posy, int w, int h);
	void loadBackground();
	SDL_Texture* loadTexture(const char* path);
	void position(Entity& paddle, Entity& ball, Entity bricks[]);
	void resetGame(Entity& paddle, Entity& ball, Entity bricks[]);
	double distanceSquared(const int& x1, const int& y1, const int& x2, const int& y2 );
	collisionSide checkCollision(Entity& ball, Entity& rect);
	void input(Entity& paddle, Entity& ball, Entity bricks[]);
	void update(Entity& paddle, Entity& ball, Entity bricks[]);
	void clear();
	void write(string text, SDL_Color textColor, const int& x , const int& y);
	void render(Entity& entity);
	void renderBall(Entity& ball);
	void display();
	void clean();
	bool running() {
		return isRunning;
	}
private:
	bool isRunning = false;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;
	int fontSize=24;
	bool gameStarted = false;
	bool ballFired = false;
	int livesCount = 3;
	SDL_Rect textRect;
	Mix_Chunk* brickHitSound;
};

#endif
