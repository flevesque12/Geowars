#include "GameObject.h"
#include "Utils.h"
#include "AppDefines.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer)
{
	isActive = true;
	if (!objectTexture.loadFromFile(imagePath, renderer, sizeMultiplier)) {
		SDL_Log("Failed to load arrow texture !");
	}

	bounds = new SDL_Rect({ objectTexture.getWidth(), objectTexture.getHeight(), objectTexture.getWidth(), objectTexture.getHeight() });

	setCenter();
	setRadius();
}

GameObject::~GameObject()
{
	objectTexture.free();
}

void GameObject::virtualizingFunction()
{
	// Used to make the class virtual
}

// Sets the orientation of the object according to its angle
void GameObject::setOrientation()
{
	this->radAngle = atan2((double)objectYDir, (double)objectXDir);
	this->degAngle = Utils::degToRad(radAngle);
	setCenter();
}

// Gets the movement vector of the object
void GameObject::getVector(double * firstX, double * firstY, double * cosAngle, double * sinAngle)
{
	radAngle = atan2((double)objectYDir, (double)objectXDir);

	radius = (double)objectTexture.getWidth() * MULTIPLIER_HALF;

	*cosAngle = cos(radAngle);
	*sinAngle = sin(radAngle);

	*firstX = zeroX + (radius * *cosAngle);
	*firstY = zeroY + (radius * *sinAngle);
}

void GameObject::setCenter()
{
	zeroX = bounds->x + objectTexture.getWidth() * MULTIPLIER_HALF;
	zeroY = bounds->y + objectTexture.getHeight() * MULTIPLIER_HALF;
}

void GameObject::setRadius()
{
	radius = (double)objectTexture.getWidth() * MULTIPLIER_HALF;
}

void GameObject::render(SDL_Renderer* renderer, int relativeX, int relativeY)
{
	objectTexture.render(bounds->x - relativeX, bounds->y - relativeY, renderer, NULL, degAngle);
}

AppTexture GameObject::getTexture()
{
	return objectTexture;
}

int GameObject::getXDir()
{
	return objectXDir;
}

int GameObject::getYDir()
{
	return objectYDir;
}

int GameObject::getXPos()
{
	return bounds->x;
}

int GameObject::getYPos()
{
	return bounds->y;
}

void GameObject::setXDir(int data)
{
	objectXDir = data;
}

void GameObject::setYDir(int data)
{
	objectYDir = data;
}

void GameObject::setXPos(int data)
{
	bounds->x += data;
}

void GameObject::setYPos(int data)
{
	bounds->y += data;
}

SDL_Rect GameObject::getBounds()
{
	return *bounds;
}