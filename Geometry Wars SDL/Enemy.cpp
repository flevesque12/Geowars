#pragma once
#include "Enemy.h"

Enemy::Enemy() {
	this->velX = enemyVelocity;
	this->velY = enemyVelocity;
	this->spawnEnemyPosX = 0;
	this->spawnEnemyPosY = 0;
}

Enemy::~Enemy()
{
}

Enemy::Enemy(int x, int y) {
	this->velX = enemyVelocity;
	this->velY = enemyVelocity;
	this->spawnEnemyPosX = x;
	this->spawnEnemyPosY = y;
}

Enemy::Enemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer * renderer) : GameObject(imagePath, sizeMultiplier, renderer)
{
	this->velX = enemyVelocity;
	this->velY = enemyVelocity;
	setXPos(x);
	setYPos(y);
}

bool Enemy::CheckCollision(SDL_Rect &collideFrom, SDL_Rect &collideTo) {
	return SDL_HasIntersection(&collideFrom, &collideTo);
}

int Enemy::GetEnemyXpos() {
	return this->spawnEnemyPosX;
}

int Enemy::GetEnemyYpos() {
	return this->spawnEnemyPosY;
}

void Enemy::SetEnemyXpos(int posX) {
	this->spawnEnemyPosX = posX;
}

void Enemy::SetEnemyYpos(int posY) {
	this->spawnEnemyPosY = posY;
}

void Enemy::reduceHealth()
{
	health--;
	// Sets the enemy transparency according to its remaining healthpoints
	if (startingHealth > ONE) {
		int newAlpha = COLOR_MAX * health / startingHealth;
		getTexture().setAlpha(newAlpha);
	}
}

int Enemy::getHealth()
{
	return health;
}

int Enemy::getStartingHealth()
{
	return startingHealth;
}