#pragma once
#include "GameObject.h"
#include "AppDefines.h"
class Enemy :
	public GameObject
{
protected:

	const int enemyVelocity = 5;

	int spawnEnemyPosX = 0;
	int spawnEnemyPosY = 0;

	int velX, velY;

	int GetEnemyXpos();

	int GetEnemyYpos();

	void SetEnemyXpos(int posX);

	void SetEnemyYpos(int posY);
	int health, startingHealth;

public:
	Enemy();
	~Enemy();
	Enemy(int x, int y);
	Enemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	bool CheckCollision(SDL_Rect &collideFrom, SDL_Rect &collideTo);
	virtual void EnemyMovement(int limitX, int limitY) {};
	void reduceHealth();
	int getHealth();
	int getStartingHealth();
};
