#include "RenderWindow.h"

Uint32 frameStart;
Uint32 frameTime;

int main(int argc, char* argv[]) {
	RenderWindow gameWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h);

	SDL_Texture* paddleTex = gameWindow.loadTexture("Assets/paddle.png");
	SDL_Texture* ballTex = gameWindow.loadTexture("Assets/ball_red.png");
	SDL_Texture* brickTex = gameWindow.loadTexture("Assets/brick.png");

	Entity paddle(window_w / 2 - (paddle_w) / 2, window_h - paddle_h - 16, paddleTex);
	Entity ball(window_w / 2, window_h - (paddle_h + ball_r)-16, ballTex);
	Entity bricks[brick_rows*brick_cols];

	for (int i = 0; i < brick_rows*brick_cols ; ++i){
			bricks[i] = {
						12+(i%brick_cols)*(brick_w+10),
						brick_h*3 + (i/brick_cols)*(brick_h+10),
						brickTex};
			bricks[i].setSize(brick_w, brick_h);
	}
	paddle.setSize(paddle_w , paddle_h);
	ball.setSize(ball_r*2, ball_r*2 );

    ball.speed = ball_speed;
    paddle.speed = paddle_speed;
    gameWindow.changeLevel(bricks,1);
    gameWindow.loadHighscore("Assets/highscore.txt");

	while (gameWindow.running()) {
		frameStart = SDL_GetTicks();
		gameWindow.clear();
		gameWindow.loadBackground();
		gameWindow.input(paddle, ball, bricks);
		gameWindow.update(paddle, ball, bricks);
		gameWindow.render(paddle);
		gameWindow.renderBall(ball);
		for(int i=0;i<brick_rows*brick_cols;++i)
			if (bricks[i].isActive) gameWindow.render(bricks[i]);
		gameWindow.display();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) SDL_Delay(DELAY_TIME - frameTime);
	}
	gameWindow.clean();
	return 0;
}
