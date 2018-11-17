#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	// Variables
	long int birthTime;

	// Constructor
	Projectile(std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);

	// Destructor
	~Projectile();

	// Methods
	void place(GameObject* parent);
	void replace();

private:
	// Constructor
	Projectile();
	bool isInitialized;
};

#endif // !PROJECTILE_H
