#pragma once
#include "PingpongEnemy.h"

PingpongEnemy::PingpongEnemy() {
}

PingpongEnemy::PingpongEnemy(SDL_Renderer *renderer) {
	objectTexture.loadFromFile("Images/ping.png", renderer, MULTIPLIER_FULL);

	bounds = new SDL_Rect({ (int)((WIDTH_SCREEN)* MULTIPLIER_HALF), (int)((HEIGHT_SCREEN)* MULTIPLIER_HALF), objectTexture.getWidth(), objectTexture.getHeight() });
}

PingpongEnemy::PingpongEnemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer) : Enemy(x, y, imagePath, sizeMultiplier, renderer) {
	objectTexture.loadFromFile("Images/ping.png", renderer, MULTIPLIER_FULL);
	bounds = new SDL_Rect({ x, y, objectTexture.getWidth(), objectTexture.getHeight() });
	health = startingHealth = PING_PONG_HEALTH;
	pongXVel = pongYVel = PINT_PONG_SPEED;
};

PingpongEnemy::~PingpongEnemy() {
	objectTexture.free();
}

int PingpongEnemy::GetPoint() {
	return pointValue;
}

void PingpongEnemy::EnemyMovement(int limitX, int limitY) {
	srand((unsigned int)time(NULL));
	int ran = rand() % 3;

	if (ran == 0) {
		bounds->x += pongXVel;
	}
	else if (ran == 1)
	{
		bounds->y += pongYVel;
	}
	else if (ran == 2) {
		bounds->y += pongYVel;
		bounds->x += pongXVel;
	}

	//bounds->x += pongXVel;

	if (bounds->x > limitX - bounds->w * MULTIPLIER_HALF) {
		pongXVel = -pongXVel;
	}

	if (bounds->x < 0) {
		pongXVel = -pongXVel;
	}

	//bounds->y += pongYVel;

	if (bounds->y > limitY - bounds->h * MULTIPLIER_HALF) {
		pongYVel = -pongYVel;
	}

	if (bounds->y < 0) {
		pongYVel = -pongYVel;
	}
}