#pragma once
#include "SDL.h"
#include "AppTexture.h"
#include "AppDefines.h"
#include "Enemy.h"
#include "vector2D.h"

class RoamerEnemy : public Enemy {
public:

	enum RDIR
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	int ROAM_Vel = 5;

	RoamerEnemy();
	~RoamerEnemy();
	RoamerEnemy(SDL_Renderer *renderer, int x, int y);
	RoamerEnemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	int GetPoint();

	void EnemyMovement();

private:
	//start pos of the enemy
	int spawnPosX, spawnPosY;

	//velocity of the enemy
	int velX, velY;

	static const int pointValue = 10;
	//AppTexture texture;
	Vector2D *vector2;
};
