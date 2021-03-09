#ifndef Entity_h
#define Entity_h

#include <SDL.h>

const int brick_w = 100;
const int brick_h = 25;

const int paddle_w = 2* 96;
const int paddle_h = 16;

const int ball_r = 32;
const int paddle_speed = 8;
const int ball_speed = 8;

class Entity {
public:
	bool isActive = true;
	int x, y;
	int Vx = 0, Vy = 0;
	Entity(const int& p_x, const int& p_y, SDL_Texture* p_tex);
	Entity();
	int getW();
	int getH();
	void setSize(const int& width, const int& height);
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();
	SDL_Rect rect;
private:
	SDL_Rect currentFrame;
	SDL_Texture* tex = nullptr;
};

#endif