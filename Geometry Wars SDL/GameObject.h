#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "AppIncludes.h"
#include "AppTexture.h"

class GameObject
{
public:
	// Variables
	double degAngle;
	bool isActive;

	// Constructor
	GameObject(std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer);
	// Destructor

	~GameObject();

	// Methods
	AppTexture getTexture();
	void setOrientation();
	void render(SDL_Renderer* renderer, int relativeX = 0, int relativeY = 0);
	void getVector(double* firstX, double* firstY, double* cosAngle, double* sinAngle);
	void setCenter();
	void setRadius();
	int getXDir();
	int getYDir();
	int getXPos();
	int getYPos();
	void setXDir(int data);
	void setYDir(int data);
	void setXPos(int data);
	void setYPos(int data);
	SDL_Rect getBounds();

protected:
	// Variables
	SDL_Rect* bounds;
	AppTexture objectTexture;
	int objectXDir, objectYDir;
	double radius, radAngle, zeroX, zeroY, cosA, sinA;

	// Consctructor
	GameObject();

private:
	// Method to make the class virtual
	virtual void virtualizingFunction();
};

#endif // !GAMEOBJECT_H
