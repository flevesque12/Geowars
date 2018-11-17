#pragma once
#include "Enemy.h"
#include "AppDefines.h"

class PingpongEnemy :public Enemy {
public:
	int pongXVel;
	int pongYVel;

	PingpongEnemy();
	PingpongEnemy(SDL_Renderer *renderer);
	PingpongEnemy(int x, int y, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	~PingpongEnemy();

	int GetPoint();

	void EnemyMovement(int limitX, int limitY) override;

private:
	static const int pointValue = 30;
	int xpos = 0;
	int ypos = 0;
};
