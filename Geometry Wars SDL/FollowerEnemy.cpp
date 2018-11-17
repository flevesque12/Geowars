#pragma once
#include "FollowerEnemy.h"

FollowerEnemy::FollowerEnemy() {
}

FollowerEnemy::~FollowerEnemy()
{
	objectTexture.free();
}

FollowerEnemy::FollowerEnemy(SDL_Renderer *renderer) {
	objectTexture.loadFromFile("Images/follower64.png", renderer, 1);

	bounds = new SDL_Rect({ 10, 10, objectTexture.getWidth(), objectTexture.getHeight() });
}

FollowerEnemy::FollowerEnemy(Game* thisgame, int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer) : Enemy(x, y, imagePath, sizeMultiplier, renderer) {
	this->thisgame = thisgame;
	objectTexture.loadFromFile(imagePath, renderer, MULTIPLIER_FULL);
	bounds = new SDL_Rect({ x, y, objectTexture.getWidth(), objectTexture.getHeight() });
	health = startingHealth = FOLLOWER_HEALTH;
	roamVel = FOLLOWER_SPEED;
}

void FollowerEnemy::EnemyMovement() {
	/*bounds->x = playerX;
	bounds->y = playerY;*/
	/*
	do {
	bounds->x++;
	bounds->y++;
	} while (bounds->x == playerX || bounds->y == playerY);
	*/
}

void FollowerEnemy::EnemyMovement(int limitX, int limitY) {
	if (thisgame->getPlayer()->getTexture().getRenderQuad().x < bounds->x - thisgame->getCamera().x) {
		bounds->x -= roamVel;
	}
	else if (thisgame->getPlayer()->getTexture().getRenderQuad().x > bounds->x - thisgame->getCamera().x) {
		bounds->x += roamVel;
	}
	else {
		bounds->x += ZERO;
	}

	if (thisgame->getPlayer()->getTexture().getRenderQuad().y < bounds->y - thisgame->getCamera().y) {
		bounds->y -= roamVel;
	}
	else if (thisgame->getPlayer()->getTexture().getRenderQuad().y > bounds->y - thisgame->getCamera().y) {
		bounds->y += roamVel;
	}
	else {
		bounds->y += ZERO;
	}
}

int FollowerEnemy::GetPoint() {
	return pointValue;
}