#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int posx, int posy, int w, int h) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << "SDL_Init error" <<' '<<SDL_GetError()<<endl;
	window = SDL_CreateWindow(title, posx, posy, w, h, SDL_WINDOW_SHOWN);
	if (!window)
		cout << "Can't create Window" << endl;
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		cout << "Can't create Renderer" << endl;
	}
	isRunning = true;
	font = TTF_OpenFont("Resources/font.ttf", fontSize);
}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) cout << "Failed at loading texture" << endl;
	return texture;
}

void RenderWindow::resetGame(Entity& paddle, Entity& ball, Entity bricks[]) {
	gameStarted = false;
	ball.Vx = 0;
	ball.Vy = 0;
	paddle.x = window_w / 2 - (paddle_w) / 2;
	paddle.y = window_h - paddle_h - 16;
	ball.x = window_w / 2 - ball_r / 2;
	ball.y = window_h - (paddle_h + ball_r) - 16;
	for (int i = 0; i < brick_cols * brick_rows; ++i)
		bricks[i].isActive = true;
}

void RenderWindow::input(Entity& paddle, Entity& ball, Entity bricks[]) {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) isRunning = false;
	if (keystates[SDL_SCANCODE_ESCAPE]) isRunning = false;
	if (keystates[SDL_SCANCODE_SPACE]) {
		if (gameStarted == false) {
			gameStarted = true;
			ball.Vy = -ball_speed;
		}
	}
	if (keystates[SDL_SCANCODE_LEFT]) {
		paddle.x -= paddle_speed;
		if (!gameStarted && paddle.x > 0) ball.x -= paddle_speed;
	}
	if (keystates[SDL_SCANCODE_RIGHT]) {
		paddle.x += paddle_speed;
		if (!gameStarted && paddle.x < window_w - paddle_w) ball.x += paddle_speed;
	}
}

void RenderWindow::update(Entity& paddle, Entity& ball, Entity bricks[]) {

	if (SDL_HasIntersection(&(ball.rect), &(paddle.rect))) {
		double rel = (paddle.x + (paddle_w / 2)) - (ball.x + (ball_r / 2));
		double norm = rel / (paddle_w / 2);
		double bounce = norm * (5 * PI / 12);
		ball.Vy = -ball_speed * cos(bounce);
		ball.Vx = ball_speed * -sin(bounce);
	}

	if (ball.x + ball_r >= window_w) ball.Vx = -ball.Vx;
	if (ball.x <= 0) ball.Vx = -ball.Vx;
	if (ball.y <= 0) ball.Vy = -ball.Vy;
	ball.x += ball.Vx;
	ball.y += ball.Vy;

	if (paddle.x < 0) paddle.x = 0;
	if (paddle.x + paddle_w > window_w) paddle.x = window_w - paddle_w;
	bool brickHit = false;
	int temp = 0;
	for (int i = 0; i < brick_cols * brick_rows; ++i) {
		if (SDL_HasIntersection(&(bricks[i].rect), &(ball.rect)) && bricks[i].isActive) {
			bricks[i].isActive = false;
			brickHit = true;
			temp = i;
		}
	}
	if (brickHit) {
		//if (ball.y <= bricks[temp].y) { ball.Vy = -ball.Vy;}
		//if (ball.y >= bricks[temp].y) { ball.Vy = -ball.Vy;}


		double rel = (bricks[temp].x + (brick_w / 2)) - (ball.x + (ball_r / 2));
		double norm = rel / (brick_w / 2);
		double bounce = norm * (2* PI / 12);
		ball.Vy = ball_speed * cos(bounce);
		ball.Vx = ball_speed * -sin(bounce);
	}
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity, float scale_w, float scale_h) {

	SDL_Rect srcRect;
	srcRect.x = entity.getCurrentFrame().x;
	srcRect.y = entity.getCurrentFrame().y;
	srcRect.w = entity.getCurrentFrame().w;
	srcRect.h = entity.getCurrentFrame().h;
	SDL_Rect desRect;
	desRect.x = entity.x;
	desRect.y = entity.y;
	desRect.w = double(entity.getCurrentFrame().w) * scale_w;
	desRect.h = double(entity.getCurrentFrame().h) * scale_h;

	entity.rect = desRect;
	SDL_RenderCopy(renderer, entity.getTex(),&srcRect, &desRect);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

void RenderWindow::clean() {
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
