#pragma once
#include "AppDefines.h"
#include "Enemy.h"
#include "vector2D.h"
#include "Game.h"

class FollowerEnemy : public Enemy {
public:

	int roamVel;

	FollowerEnemy();
	FollowerEnemy(SDL_Renderer *renderer);
	FollowerEnemy(Game* thisgame, int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	~FollowerEnemy();
	//FollowerEnemy(int spawnX, int spawnY, SDL_Renderer *renderer);

	int GetPoint();

	void EnemyMovement();

	void EnemyMovement(int limitX, int limitY) override;
private:
	Game* thisgame;
	//int spawnPosX, spawnPosY;

	//int velX, velY;

	static const int pointValue = 10;
	Vector2D vector;
	//AppTexture textureFollower;
};
