#pragma once
#include "RoamerEnemy.h"

RoamerEnemy::RoamerEnemy() {
}

RoamerEnemy::~RoamerEnemy()
{
	objectTexture.free();
}

RoamerEnemy::RoamerEnemy(SDL_Renderer *renderer, int x, int y) {
	//init
	spawnPosX = 0;
	spawnPosY = 0;

	velX = 0;
	velY = 0;

	//load texture of the enemy
	if (!objectTexture.loadFromFile("Images/roamer64.png", renderer, 1)) {
		SDL_Log("Failed to load roamer texture !");
	}

	//create new rect
	bounds = new SDL_Rect({ x, y, 64, 64 });
}

RoamerEnemy::RoamerEnemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer) : Enemy(x, y, imagePath, sizeMultiplier, renderer) {
	objectTexture.loadFromFile(imagePath, renderer, MULTIPLIER_FULL);
	bounds = new SDL_Rect({ x, y, objectTexture.getWidth(), objectTexture.getHeight() });
	health = startingHealth = PING_PONG_HEALTH;
}

void RoamerEnemy::EnemyMovement() {
	srand((unsigned int)time(NULL));
	int ran = rand() % 5;

	if (ran == 0) {
		bounds->x += ROAM_Vel;
	}
	else if (ran == 1)
	{
		bounds->y += ROAM_Vel;
	}
	else if (ran == 2) {
		bounds->y += ROAM_Vel;
		bounds->x += ROAM_Vel;
	}
	else if (ran == 3)
	{
		bounds->y -= ROAM_Vel;
	}
	else if (ran == 4)
	{
		bounds->x -= ROAM_Vel;
	}
}

int RoamerEnemy::GetPoint() {
	return pointValue;
}