#include "Projectile.h"
#include "AppDefines.h"
#include "AppIncludes.h"

Projectile::Projectile()
{
}

Projectile::Projectile(std::string imagePath, float sizeMultiplier, SDL_Renderer * renderer) : GameObject(imagePath, sizeMultiplier, renderer)
{
	isInitialized = false;
	birthTime = SDL_GetTicks();
}

Projectile::~Projectile()
{
}

void Projectile::place(GameObject* parent)
{
	if (!isInitialized) {
		parent->getVector(&zeroX, &zeroY, &cosA, &sinA);
		bounds->x = (int)(zeroX + cosA * PLAYER_MISSILE_SPEED - getTexture().getWidth() * MULTIPLIER_HALF);
		bounds->y = (int)(zeroY + sinA * PLAYER_MISSILE_SPEED - getTexture().getHeight() * MULTIPLIER_HALF);
		isInitialized = true;
	}
}

// Moves the projectile to its next place
void Projectile::replace()
{
	bounds->x = (int)(bounds->x + cosA * PLAYER_MISSILE_SPEED);
	bounds->y = (int)(bounds->y + sinA * PLAYER_MISSILE_SPEED);
}