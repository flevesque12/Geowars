#pragma once

#ifndef GAME_H
#define GAME_H

#include "AppDefines.h"
#include "AppEnums.h"
#include "AppIncludes.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

class Game
{
public:
	// Constructor
	Game();

	// Destructor
	virtual ~Game();

	// Methods
	int initialize();
	void execute();
	void freeMemory();
	Player* getPlayer();
	SDL_Rect getCamera();
	int getWindowWidth();
	int getWindowHeight();

private:
	// Variables
	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Event gameEvent;
	SDL_Rect* camera;
	SDL_Rect* bgRect;
	AppTexture bgTexture;

	TTF_Font *font = NULL;
	AppTexture scoreTexture, titleTexture, gameOverTexture, resultTexture, quitOrderTexture;
	AppTexture buttonPlayTexture, buttonManualTexture, buttonExitTexture;
	std::vector<AppTexture*> manualText, pauseText;
	SDL_Color textColor;
	std::string textScore;
	int fontSize;

	SDL_Texture* spriteArrow;
	SDL_Rect clips[SPRITES_COLUMNS * SPRITES_LINES], spriteRectangle;
	int spriteCmp, spriteTick, spriteX, spriteY, spriteMenuPosition, spriteMenuTick;

	Mix_Music* musicGame = NULL;
	Mix_Chunk *soundEffectMenuMove, *soundEffectPlayerShoot, *soundEffectPlayerExplosion, *soundEffectPlayerRespawn = NULL;

	SDL_GameController* controller = NULL;
	SDL_Haptic* controllerHaptic = NULL;
	Player* player = NULL;
	std::vector<GameObject*> lives;

	std::vector<Enemy*> enemies;

	EScenes scene;
	bool isRunning, isLost, isPaused;
	int score, bestScore, windowWidth, windowHeight, levelWidth, levelHeight, playerDeathTick, playerInvulnerabilityTick, pauseTick;
	int clearColor[3];
	Uint32 start, end;

	// Methods
	void initializeSDL(int &result);
	void initializeIMG(int &result);
	void initializeTTF(int &result);
	void createWindowAndRenderer(int &result);
	void initializeController(int &result);

	void setFont(int size);
	void setTextTexture(AppTexture* texture, std::string text, int size);
	void setSprite();
	void placeSprite(AppTexture* reference);

	void setTexts(std::string path, std::vector<AppTexture*>* texts, int size);
	void getBestScore(std::string path);
	void setBestScore(std::string path, int newBestScore);

	void changeMusic(std::string path);

	void setPlayer();
	void addLife();
	void removeLife();
	void resetGame();

	void checkEnemiesPlayerBeamCollision();
	void checkEnemiesPlayerCollision();
	void checkPlayerStatus();

	void generateRandomPingPongEnemies();

	void manageEvent(SDL_Event* gameEvent);
	void updateModel();
	void drawModel();
	void updateView();
	void erase();
};

#endif // !GAME_H
