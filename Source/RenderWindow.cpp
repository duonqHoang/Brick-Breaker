#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int posx, int posy, int w, int h) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << "SDL_Init error" <<' '<<SDL_GetError()<<endl;
	window = SDL_CreateWindow(title, posx, posy, w, h, SDL_WINDOW_SHOWN);
	if (!window)
		cout << "Can't create Window" << endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		cout << "Can't create Renderer" << endl;
	}
	if (TTF_Init() == -1)
        cout<<"SDL_ttf could not initialize! SDL_ttf Error: %s\n"<< TTF_GetError();
	font = TTF_OpenFont("Assets/font.ttf", fontSize);
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        cout<< "SDL_mixer could not initialize! SDL_mixer Error: %s\n"<< Mix_GetError();
    brickHitSound = Mix_LoadWAV("Assets/brickHit.wav");
    if (brickHitSound == NULL) cout<<"failed to load sound effect"<<endl;
	isRunning = true;

}

SDL_Texture* RenderWindow::loadTexture(const char* path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) cout << "Failed at loading texture" << endl;
	return texture;
}

void RenderWindow::loadBackground(){
    SDL_Texture* bgTexture = loadTexture("Assets/background_blue.png");
    for (int i = 0; i<13; ++i)
        for (int j = 0;j<12; ++j){
            SDL_Rect bgRect;
            bgRect.x = 64*j;
            bgRect.y = 64*i;
            bgRect.w = 64;
            bgRect.h = 64;
            SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
        }
};

void RenderWindow::position(Entity& paddle, Entity& ball, Entity bricks[]) {
    ball.Vx = 0;
	ball.Vy = 0;
	ball.speed = 8;
	paddle.x = window_w / 2 - (paddle_w) / 2;
	paddle.y = window_h - paddle_h - 16;
	ball.x = window_w / 2;
	ball.y = window_h - (paddle_h + ball_r) - 16;
    ballFired = false;
}

void RenderWindow::resetGame(Entity& paddle, Entity& ball, Entity bricks[]) {
	livesCount = 3;
	position(paddle,ball,bricks);
	for (int i = 0; i < brick_cols * brick_rows; ++i)
		bricks[i].isActive = true;
	gameStarted = false;
}

void RenderWindow::write(string text, SDL_Color textColor, const int& x, const int& y) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == NULL) cout << "Failed to render text surface! Error: " << TTF_GetError();
	else {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;
		textRect.x = x - textRect.w/2;
		textRect.y = y;

		SDL_FreeSurface(textSurface);
		SDL_RenderCopy(renderer, texture, NULL, &textRect);
		SDL_DestroyTexture(texture);
	}
}

double RenderWindow::distanceSquared(const int& x1, const int& y1, const int& x2, const int& y2 ){
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

collisionSide RenderWindow::checkCollision(Entity& ball, Entity& rect){
    float cX, cY;
    if( ball.x < rect.x )
    {
        cX = rect.x;
    }
    else if( ball.x > rect.x + rect.getW() )
    {
        cX = rect.x + rect.getW();
    }
    else
    {
        cX = ball.x;
    }
    if( ball.y < rect.y )
    {
        cY = rect.y;
    }
    else if( ball.y > rect.y + rect.getH() )
    {
        cY = rect.y + rect.getH();
    }
    else
    {
        cY = ball.y;
    }

    //If the closest point is inside the circle
    if( distanceSquared( ball.x, ball.y, cX, cY ) < ball_r * ball_r )
    {
        //This box and the circle have collided
        int dX = rect.x + rect.getW()/2;
        int dY = rect.y + rect.getH()/2;
        if ( ( cX < dX || cX > dX)  && cY > rect.y && cY < rect.y + rect.getH() )
            return horizontal;
        else return vertical;
    }

    //If the shapes have not collided
    return none;
}

void RenderWindow::input(Entity& paddle, Entity& ball, Entity bricks[]) {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) isRunning = false;
	if (keystates[SDL_SCANCODE_ESCAPE]) isRunning = false;
	if (keystates[SDL_SCANCODE_SPACE]) {
		if (ballFired == false) {
			ballFired = true;
			ball.Vy = -ball.speed;
		}
	}
	if (keystates[SDL_SCANCODE_LEFT]) {
		paddle.x -= paddle.speed;
		if (!ballFired && paddle.x > 0) ball.x -= paddle.speed;
	}
	if (keystates[SDL_SCANCODE_RIGHT]) {
		paddle.x += paddle.speed;
		if (!ballFired && paddle.x < window_w - paddle_w) ball.x += paddle.speed;
	}
}

void RenderWindow::update(Entity& paddle, Entity& ball, Entity bricks[]) {
    if (livesCount < 0){
        resetGame(paddle, ball, bricks);
        return;
    }

	if (checkCollision(ball, paddle) == vertical) {
		double rel = (paddle.x + (paddle_w / 2)) - (ball.x + (ball_r / 2));
		double norm = rel / (paddle_w / 2);
		double bounce = norm * (5 * PI / 12);
		ball.speed += 0.3;
		ball.Vy = -ball.speed * cos(bounce);
		ball.Vx = ball.speed * -sin(bounce);
	}
	else if (checkCollision(ball, paddle) == horizontal){
        ball.Vx = -ball.Vx;
	}

	if (ball.x + ball_r >= window_w) ball.Vx = -ball.Vx;
	if (ball.x - ball_r <= 0) ball.Vx = -ball.Vx;
	if (ball.y - ball_r <= 0) ball.Vy = -ball.Vy;
	if (ball.y + ball_r > window_h) {
        livesCount--;
        position(paddle,ball,bricks);
	}
	ball.x += ball.Vx;
	ball.y += ball.Vy;

	if (paddle.x < 0) paddle.x = 0;
	if (paddle.x + paddle_w > window_w) paddle.x = window_w - paddle_w;

	for (int i = 0; i < brick_cols * brick_rows; ++i) {
		if (checkCollision(ball,bricks[i]) == vertical && bricks[i].isActive){
            ball.Vy = -ball.Vy;
            bricks[i].isActive = false;
            Mix_PlayChannel(-1,brickHitSound,0);
		}
		else if (checkCollision(ball,bricks[i]) == horizontal && bricks[i].isActive){
            ball.Vx = -ball.Vx;
            bricks[i].isActive = false;
            Mix_PlayChannel(-1,brickHitSound,0);
		}
	}

	bool allBroken = true;
	for(int i=0;i<brick_cols*brick_rows;++i){
        if (bricks[i].isActive){
            allBroken = false;
            break;
        }
	}
	if (allBroken){
    position(paddle, ball, bricks);
	}
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity) {

	SDL_Rect srcRect;
	srcRect.x = entity.getCurrentFrame().x;
	srcRect.y = entity.getCurrentFrame().y;
	srcRect.w = entity.getCurrentFrame().w;
	srcRect.h = entity.getCurrentFrame().h;
	SDL_Rect desRect;
	desRect.x = entity.x;
	desRect.y = entity.y;
	desRect.w = entity.getCurrentFrame().w;
	desRect.h = entity.getCurrentFrame().h;

	entity.rect = desRect;
	SDL_RenderCopy(renderer, entity.getTex(),&srcRect, &desRect);
}

void RenderWindow::renderBall(Entity& ball){
    SDL_Rect desrect;
    desrect.x = ball.x - ball_r;
    desrect.y = ball.y - ball_r;
    desrect.w = ball.getCurrentFrame().w;
    desrect.h = ball.getCurrentFrame().h;

    ball.rect = desrect;
    SDL_RenderCopy(renderer, ball.getTex(), NULL, &desrect);
}

void RenderWindow::display() {
    SDL_Color textColor = {255,255,255};
    if (!ballFired) write ("Press Space !",textColor, window_w/2, window_h - 200);
    //textColor = {255,0,255};
	write("Lives: ",textColor,window_w - 150,20);
	write(to_string(livesCount), textColor,window_w -50,20);
	SDL_RenderPresent(renderer);
}

void RenderWindow::clean() {
    Mix_FreeChunk(brickHitSound);
    brickHitSound = NULL;
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
