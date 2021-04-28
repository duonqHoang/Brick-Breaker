#ifndef Entity_h
#define Entity_h

#include <SDL.h>

enum parameters{
    window_w = 64*11,
    window_h = 64*13,
    brick_w = 128,
    brick_h = 32,
    brick_rows = 12,
    brick_cols = 5,
    paddle_w = 156,
    paddle_h = 24,
    ball_r = 32/2,
    ball_speed = 8,
    paddle_speed = 8,
    max_level = 5
};

enum collisionSide{
    horizontal,
    vertical,
    none
};

class Entity {
public:
	bool isActive = true;
	float x, y;
	float Vx = 0, Vy = 0, speed = 0;
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
	SDL_Texture* tex = NULL;
};

#endif
