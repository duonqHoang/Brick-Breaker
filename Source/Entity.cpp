#include "Entity.h"

Entity::Entity() {};
Entity::Entity(const int& p_x, const int& p_y, SDL_Texture* p_tex){
	x = p_x;
	y = p_y;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 0;
}

int Entity::getW() {
	return currentFrame.w;
}

int Entity::getH() {
	return currentFrame.h;
}

void Entity::setSize(const int& width, const int& height) {
	currentFrame.w = width;
	currentFrame.h = height;
}

SDL_Rect Entity::getCurrentFrame() {
	return currentFrame;
}

SDL_Texture* Entity::getTex() {
	return tex;
}