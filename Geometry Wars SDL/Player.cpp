#include "AppDefines.h"
#include "AppEnums.h"
#include "Game.h"
#include "Player.h"
#include "SDL.h"
#include "Utils.h"

Player::Player() {
}

Player::Player(int screenWidth, int screenHeight, std::string imagePath, float sizeMultiplier, SDL_Renderer* renderer) : GameObject(imagePath, sizeMultiplier, renderer)
{
	isAlive = true;
	isAllowedToShot = true;
	isShooting = false;
	setXPos((int)(screenWidth * MULTIPLIER_QUARTER - bounds->w * MULTIPLIER_FULL_AND_HALF));
	setYPos((int)(screenHeight * MULTIPLIER_QUARTER - bounds->h * MULTIPLIER_FULL_AND_HALF));
}

Player::~Player()
{
}

void Player::manageRightAxis(SDL_GameController* controller)
{
	if (isAlive) {
		if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) < -JOYSTICK_DEAD_ZONE) {
			setXDir(NEGATIVE);
			isShooting = true;
		}
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) > JOYSTICK_DEAD_ZONE) {
			setXDir(POSITIVE);
			isShooting = true;
		}
		else {
			setXDir(NEUTRAL);
		}

		if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) < -JOYSTICK_DEAD_ZONE) {
			setYDir(NEGATIVE);
			isShooting = true;
		}
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) > JOYSTICK_DEAD_ZONE) {
			setYDir(POSITIVE);
			isShooting = true;
		}
		else {
			setYDir(NEUTRAL);
		}
	}
}

void Player::manageLeftAxis(SDL_GameController * controller, int levelWidth, int levelHeight)
{
	if (isAlive) {
		if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < -JOYSTICK_DEAD_ZONE) {
			if (getXPos() > ZERO) {
				setXPos(-PLAYER_SPEED);
			}
		}
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > JOYSTICK_DEAD_ZONE) {
			if (getXPos() + bounds->w < levelWidth) {
				setXPos(PLAYER_SPEED);
			}
		}

		if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -JOYSTICK_DEAD_ZONE) {
			if (getYPos() > ZERO) {
				setYPos(-PLAYER_SPEED);
			}
		}
		else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > JOYSTICK_DEAD_ZONE) {
			if (getYPos() + bounds->h < levelHeight) {
				setYPos(PLAYER_SPEED);
			}
		}
	}
}

void Player::manageLeftKeyboard(const Uint8* states, SDL_Event* gameEvent, int levelWidth, int levelHeight)
{
	if (isAlive) {
		if (states[SDL_SCANCODE_Q] || states[SDL_SCANCODE_A]) {
			if (getXPos() > ZERO) {
				setXPos(-PLAYER_SPEED);
			}
		}
		else if (states[SDL_SCANCODE_D]) {
			if (getXPos() + bounds->w < levelWidth) {
				setXPos(PLAYER_SPEED);
			}
		}

		if (states[SDL_SCANCODE_Z] || states[SDL_SCANCODE_W]) {
			if (getYPos() > ZERO) {
				setYPos(-PLAYER_SPEED);
			}
		}
		else if (states[SDL_SCANCODE_S]) {
			if (getYPos() + bounds->h < levelHeight) {
				setYPos(PLAYER_SPEED);
			}
		}
	}
}

void Player::manageRightKeyboard(const Uint8* states, SDL_Event* gameEvent)
{
	if (isAlive) {
		if (states[SDL_SCANCODE_LEFT]) {
			setXDir(NEGATIVE);
			isShooting = true;
		}
		else if (states[SDL_SCANCODE_RIGHT]) {
			setXDir(POSITIVE);
			isShooting = true;
		}
		else {
			setXDir(NEUTRAL);
		}

		if (states[SDL_SCANCODE_UP]) {
			setYDir(NEGATIVE);
			isShooting = true;
		}
		else if (states[SDL_SCANCODE_DOWN]) {
			setYDir(POSITIVE);
			isShooting = true;
		}
		else {
			setYDir(NEUTRAL);
		}
	}
}

void Player::shot(SDL_Renderer * renderer)
{
	if (isAllowedToShot && isShooting && (int)SDL_GetTicks() >= shootDelayTick + PLAYER_SHOOT_DELAY) {
		// Adds a new projectile
		playerProjectiles.push_back(new Projectile("Images/shoot.png", MULTIPLIER_HALF, renderer));
		// Actualizes the shoot delay
		shootDelayTick = SDL_GetTicks();
		// Places each projectile
		for (int i = ZERO; i < (int)playerProjectiles.size(); i++) {
			playerProjectiles[i]->place(this);
		}
	}
}

void Player::setProjectiles()
{
	for (int i = ZERO; i < (int)playerProjectiles.size(); i++) {
		// Destroys the projectile if its lifespan is reached
		if (SDL_GetTicks() - playerProjectiles[i]->birthTime > shootLifeSpan) {
			playerProjectiles[i]->~Projectile();
			playerProjectiles.erase(playerProjectiles.begin() + i);
		}
		else {
			// Moves the projectile
			playerProjectiles[i]->replace();
		}
	}
}

void Player::renderProjectiles(SDL_Renderer * renderer)
{
	for (int i = ZERO; i < (int)playerProjectiles.size(); i++) {
		if (playerProjectiles[i]->isActive) {
			playerProjectiles[i]->render(renderer);
		}
	}
}

void Player::destroySpaceShip()
{
	isAlive = isInvulnerable = true;

	isAllowedToShot = false;
	getTexture().setAlpha(ALPHA_INVULNERABLE);
}

void Player::respawn()
{
	isInvulnerable = false;
	isAllowedToShot = true;
	getTexture().setAlpha(ALPHA_MAX);
}