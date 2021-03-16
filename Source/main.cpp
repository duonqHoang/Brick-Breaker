#include "RenderWindow.h"

Uint32 frameStart;
Uint32 frameTime;

int main(int argc, char* argv[]) {
	RenderWindow gameWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h);

	SDL_Texture* paddleTex = gameWindow.loadTexture("Assets/paddle.png");
	SDL_Texture* ballTex = gameWindow.loadTexture("Assets/ball.png");
	SDL_Texture* brickTex1 = gameWindow.loadTexture("Assets/brick1.png");
	SDL_Texture* brickTex2 = gameWindow.loadTexture("Assets/brick2.png");

	Entity paddle(window_w / 2 - (paddle_w) / 2, window_h - paddle_h - 16, paddleTex);
	Entity ball(window_w / 2 - ball_r/2, window_h - (paddle_h + ball_r) - 16, ballTex);
	Entity bricks[brick_rows*brick_cols];

	for (int i = 0; i < brick_rows*brick_cols ; ++i){
			bricks[i] = {
						15+(i%brick_cols)*(brick_w+10),
						brick_h*3 + (i/brick_cols)*(brick_h+10),
						(i/brick_cols % 2 == 0 ? brickTex1 : brickTex2) };
			bricks[i].setSize(brick_w, brick_h);
	}

	paddle.setSize(paddle_w , paddle_h);
	ball.setSize(ball_r  , ball_r  );

	while (gameWindow.running()) {
		frameStart = SDL_GetTicks();
		gameWindow.clear();
		gameWindow.input(paddle, ball, bricks);
		gameWindow.update(paddle, ball, bricks);
		gameWindow.render(paddle);
		gameWindow.render(ball);
		for(int i=0;i<brick_rows*brick_cols;++i)
			if (bricks[i].isActive) gameWindow.render(bricks[i]);
		gameWindow.display();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) SDL_Delay(DELAY_TIME - frameTime);
	}
	gameWindow.clean();
	return 0;
}
