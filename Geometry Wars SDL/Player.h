#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "AppIncludes.h"
#include "AppTexture.h"
#include "Game.h"
#include "GameObject.h"
#include "Projectile.h"

class Player : public GameObject
{
public:
	// Variables
	bool isAlive, isAllowedToShot, isShooting, isInvulnerable;
	float shootLifeSpan;
	int lives, shootDelayTick;

	// Constructor
	Player(int screenWidth, int screenHeight, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	// Destructor
	~Player();

	// Methods
	void manageRightAxis(SDL_GameController* controller);
	void manageLeftAxis(SDL_GameController* controller, int levelWidth, int levelHeight);
	void manageLeftKeyboard(const Uint8* states, SDL_Event* gameEvent, int levelWidth, int levelHeight);
	void manageRightKeyboard(const Uint8* states, SDL_Event* gameEvent);

	std::vector<Projectile*> playerProjectiles;
	void shot(SDL_Renderer* renderer);
	void setProjectiles();
	void renderProjectiles(SDL_Renderer* renderer);

	void destroySpaceShip();
	void respawn();

private:
	// Constructor
	Player();
};

#endif // !PLAYER_H
