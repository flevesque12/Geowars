#include "Game.h"
#include "AppDefines.h"
#include "FollowerEnemy.h"
#include "PingpongEnemy.h"
#include "RoamerEnemy.h"
#include "Utils.h"

Game::Game()
{
	clearColor[0] = ZERO;
	clearColor[1] = ZERO;
	clearColor[2] = ZERO;
}

Game::~Game()
{
}

int Game::initialize()
{
	// Game datas
	scene = S_HOME;
	isRunning = true;
	int result = ZERO;
	getBestScore("Texts/bestscore.txt");

	// System
	SDL_ShowCursor(SDL_DISABLE);
	srand((unsigned int)time(NULL));
	initializeSDL(result);
	initializeIMG(result);
	createWindowAndRenderer(result);
	initializeTTF(result);
	initializeController(result);

	// Background texture
	bgTexture.loadFromFile("Images/space.jpg", renderer, MULTIPLIER_FULL);
	levelWidth = bgTexture.getWidth();
	levelHeight = bgTexture.getHeight();

	// Camera box
	camera = new SDL_Rect({ (int)(levelWidth * MULTIPLIER_HALF - windowWidth * MULTIPLIER_HALF), (int)(levelHeight * MULTIPLIER_HALF - windowHeight * MULTIPLIER_HALF), windowWidth, windowHeight });

	// Text boxes
	textColor = { COLOR_MAX, COLOR_MAX, COLOR_MAX };
	setTextTexture(&titleTexture, "GEOMETRY WARS SDL", (int)(fontSize * MULTIPLIER_TWICE));
	setTextTexture(&buttonPlayTexture, "PLAY", fontSize);
	setTextTexture(&buttonManualTexture, "MANUAL", fontSize);
	setTextTexture(&buttonExitTexture, "EXIT", fontSize);
	setTextTexture(&gameOverTexture, "GAME OVER", (int)(fontSize * MULTIPLIER_TWICE));
	setTextTexture(&quitOrderTexture, "Back => menu / Start => retry.", fontSize);
	setTexts("Texts/manual.txt", &manualText, fontSize);
	setTexts("Texts/pause.txt", &pauseText, (int)(fontSize * MULTIPLIER_TWICE));

	// Menu sprite
	setSprite();

	// Sounds

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("SDL_mixer could not initialize ! SDL_mixer Error: %s\n", Mix_GetError());
	}

	soundEffectMenuMove = Mix_LoadWAV(EFFECT_MOVE_MENU);
	if (soundEffectMenuMove == NULL) {
		SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s", Mix_GetError());
	}
	soundEffectPlayerShoot = Mix_LoadWAV(EFFECT_PLAYER_LASER_01);
	if (soundEffectPlayerShoot == NULL) {
		SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s", Mix_GetError());
	}
	soundEffectPlayerExplosion = Mix_LoadWAV(EFFECT_PLAYER_SHIP_EXPLOSION);
	if (soundEffectPlayerExplosion == NULL) {
		SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s", Mix_GetError());
	}
	soundEffectPlayerRespawn = Mix_LoadWAV(EFFECT_PLAYER_SHIP_RESPAWN);
	if (soundEffectPlayerRespawn == NULL) {
		SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s", Mix_GetError());
	}

	Mix_VolumeChunk(soundEffectMenuMove, (int)(MIX_MAX_VOLUME * MULTIPLIER_HALF));
	Mix_VolumeChunk(soundEffectPlayerShoot, (int)(MIX_MAX_VOLUME * MULTIPLIER_HALF));
	Mix_VolumeChunk(soundEffectPlayerExplosion, (int)(MIX_MAX_VOLUME * MULTIPLIER_HALF));
	Mix_VolumeChunk(soundEffectPlayerRespawn, (int)(MIX_MAX_VOLUME * MULTIPLIER_HALF));

	resetGame();
	return result;
}

void Game::execute()
{
	changeMusic(MUSIC_HOME);
	while (isRunning) {
		start = SDL_GetTicks();
		SDL_PollEvent(&gameEvent);
		manageEvent(&gameEvent);
		updateModel();
		erase();
		drawModel();
		updateView();
		end = SDL_GetTicks();
		if (end - start < SECOND / FPS)
			SDL_Delay((SECOND / FPS) - (end - start));
	}
}

void Game::freeMemory()
{
	// Textures release
	quitOrderTexture.free();
	resultTexture.free();
	gameOverTexture.free();
	SDL_DestroyTexture(spriteArrow);
	buttonExitTexture.free();
	buttonManualTexture.free();
	buttonPlayTexture.free();
	titleTexture.free();
	scoreTexture.free();
	bgTexture.free();	

	// Sounds release
	Mix_FreeMusic(musicGame);
	musicGame = NULL;
	Mix_FreeChunk(soundEffectMenuMove);
	Mix_FreeChunk(soundEffectPlayerShoot);
	Mix_FreeChunk(soundEffectPlayerExplosion);
	Mix_FreeChunk(soundEffectPlayerRespawn);
	soundEffectMenuMove = NULL;
	soundEffectPlayerShoot = NULL;
	soundEffectPlayerExplosion = NULL;
	soundEffectPlayerRespawn = NULL;

	// Controller release
	SDL_HapticClose(controllerHaptic);
	SDL_GameControllerClose(controller);
	controllerHaptic = NULL;
	controller = NULL;

	// Environment release
	SDL_DestroyWindow(win);
	win = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	IMG_Quit();
}

void Game::initializeSDL(int &result)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL initialization failed. SDL Error : %s", SDL_GetError());
		result = EXIT_FAILURE;
	}
}

void Game::initializeIMG(int & result)
{
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		result = EXIT_FAILURE;
	}
}

void Game::initializeTTF(int & result)
{
	if (TTF_Init() < 0) {
		SDL_Log("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
		result = EXIT_FAILURE;
	}
	else {
		// Sets the font size according to the display size
		fontSize = (int)(windowHeight * MULTIPLIER_FONT);
	}
}

void Game::createWindowAndRenderer(int & result)
{
	if (SDL_CreateWindowAndRenderer(WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_RENDERER_PRESENTVSYNC, &win, &renderer) < 0) {
		SDL_Log("Couldn't create window and renderer. SDL Error : %s", SDL_GetError());
		result = EXIT_FAILURE;
	}
	else {
		SDL_SetWindowTitle(win, "Geometry Wars SDL");
		// Gets the display size
		SDL_GetWindowSize(win, &windowWidth, &windowHeight);
	}
}

void Game::initializeController(int &result)
{
	controller = NULL;
	bool isFound = false;
	int joystickCmp = ZERO;

	// Search the first connected controller
	if (SDL_NumJoysticks()) {
		while (!isFound && joystickCmp < SDL_NumJoysticks()) {
			if (SDL_IsGameController(joystickCmp)) {
				controller = SDL_GameControllerOpen(joystickCmp);
				if (!controller) {
					SDL_Log("Could not open gamecontroller %i: %s\n", joystickCmp, SDL_GetError());
				}
				else {
					isFound = true;
					controllerHaptic = SDL_HapticOpen(ZERO);
					if (controllerHaptic == NULL) {
						SDL_Log("Could not open controllerHaptic");
					}
					else {
						if (SDL_HapticRumbleSupported(controllerHaptic)) {
							if (SDL_HapticRumbleInit(controllerHaptic) != ZERO) {
								SDL_Log("Could not initialize rumbler");
							}
						}
						else {
							SDL_Log("Rumble not supported");
						}
					}
				}
			}
			else {
				joystickCmp++;
			}
		}
	}
	else {
		SDL_Log("No joystick found.");
	}
}

void Game::setFont(int size)
{
	TTF_CloseFont(font);
	font = NULL;
	font = TTF_OpenFont("Fonts/Virtual Rave.ttf", size);
	if (font == NULL) {
		SDL_Log("Failed to load the font ! SDL_TTF Error: %s\n", TTF_GetError());
	}
}

// Used to set a text as a texture
void Game::setTextTexture(AppTexture* texture, std::string text, int size)
{
	setFont(size);
	texture->free();
	if (!texture->loadFromRenderedText(text, textColor, renderer, font)) {
		SDL_Log("Failed to text texture  : %s", text.c_str());
	}
	setFont(fontSize);
}

// Sets the menu sprite
void Game::setSprite()
{
	// Gets the sprite from the file
	SDL_Surface* spriteSurface = IMG_Load("Images/arrows.png");

	// Prepares the sprite frames
	for (int i = ZERO; i < SPRITES_LINES; i++) {
		for (int j = ZERO; j < SPRITES_COLUMNS; j++) {
			clips[i * SPRITES_COLUMNS + j].x = j * spriteSurface->w / SPRITES_COLUMNS;
			clips[i * SPRITES_COLUMNS + j].y = i * spriteSurface->h / SPRITES_LINES;
			clips[i * SPRITES_COLUMNS + j].w = spriteSurface->w / SPRITES_COLUMNS;
			clips[i * SPRITES_COLUMNS + j].h = spriteSurface->h / SPRITES_LINES;
		}
	}

	if (spriteSurface) {
		// Load the surface to the texture
		spriteArrow = SDL_CreateTextureFromSurface(renderer, spriteSurface);
		SDL_FreeSurface(spriteSurface);
	}
	else {
		SDL_Log("Error %s %i", SDL_GetError(), IMG_GetError());
	}

	// Initializes the sprite
	spriteCmp = spriteTick = spriteMenuPosition = spriteMenuTick = ZERO;
}

// Places the sprite next to a menu element
void Game::placeSprite(AppTexture * reference)
{
	spriteX = reference->getRenderQuad().x - (int)(clips[ZERO].w * MULTIPLIER_FULL_AND_HALF);
	spriteY = reference->getRenderQuad().y;
}

// Extracts the text from a .txt file and puts it into one texture per line
void Game::setTexts(std::string path, std::vector<AppTexture*>* texts, int size)
{
	std::string manualFile = path;
	std::ifstream fileIn(manualFile.c_str());
	std::string line;
	int lineCmp = ZERO;
	while (std::getline(fileIn, line)) {
		texts->push_back(new AppTexture());
		setTextTexture(texts->at(lineCmp), line, size);
		lineCmp++;
	}
}

void Game::getBestScore(std::string path)
{
	std::string manualFile = path;
	std::ifstream fileIn(manualFile.c_str());
	std::string line;
	std::getline(fileIn, line);
	std::string::size_type sz;
	bestScore = std::stoi(line, &sz);
	fileIn.close();
}

void Game::setBestScore(std::string path, int newBestScore)
{
	std::string manualFile = path;
	std::ofstream fileOut(manualFile.c_str());
	if (fileOut) {
		fileOut << std::to_string(newBestScore);
	}
	else {
		SDL_Log("Unable to write into %s", path);
	}
	fileOut.close();
}

void Game::changeMusic(std::string path)
{
	if (Mix_PlayingMusic() == ZERO) {
		Mix_HaltMusic();
	}
	else if (Mix_PausedMusic() == ONE) {
		Mix_ResumeMusic();
	}
	Mix_FreeMusic(musicGame);
	musicGame = NULL;
	musicGame = Mix_LoadMUS(path.c_str());
	if (musicGame == NULL) {
		SDL_Log("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else {
		Mix_PlayMusic(musicGame, -ONE);
	}
}

// Initializes the player object
void Game::setPlayer()
{
	player = NULL;
	player = new Player(windowWidth, windowHeight, "Images/player.png", MULTIPLIER_FULL_AND_HALF, renderer);
	player->shootLifeSpan = windowHeight * PLAYER_SHOOT_LIFESPAN_MULTIPLIER;
	lives.clear();
	player->playerProjectiles.clear();
	for (int i = ZERO; i < STARTING_LIVES; i++) {
		addLife();
	}
	player->shootDelayTick = ZERO;
}

// Adds one life to the player
void Game::addLife()
{
	player->lives++;
	lives.push_back(new GameObject("Images/player.png", MULTIPLIER_FULL, renderer));
	int place = lives.size() - ONE;
	lives[place]->setXPos(-lives[place]->getTexture().getWidth() + place * lives[place]->getTexture().getWidth());
	lives[place]->setYPos(-lives[place]->getTexture().getHeight());
	lives[place]->degAngle = -RIGHT_ANGLE;
}

// Removes one life from the player
void Game::removeLife()
{
	player->lives--;
	if (lives.size() > ZERO) {
		lives.pop_back();
	}
}

void Game::resetGame()
{
	isLost = isPaused = false;
	score = ZERO;
	setPlayer();
	enemies.clear();
	playerDeathTick = playerInvulnerabilityTick = ZERO;
	getBestScore("Texts/bestscore.txt");
}

void Game::checkEnemiesPlayerBeamCollision()
{
	for (int i = ZERO; i < (int)player->playerProjectiles.size(); i++) {
		for (int j = ZERO; j < (int)enemies.size(); j++) {
			if (player->playerProjectiles[i]->isActive && SDL_HasIntersection(&enemies[j]->getTexture().getRenderQuad(), &player->playerProjectiles[i]->getBounds())) {
				// Reduces the enemy health
				enemies[j]->reduceHealth();
				if (enemies[j]->getHealth() <= ZERO) {
					// Increments the score
					score += enemies[j]->getStartingHealth();
					// Destroys the enemy
					enemies[j]->~Enemy();
					enemies.erase(enemies.begin() + j);
				}
				// Deactivates the projectile
				player->playerProjectiles[i]->isActive = false;
			}
		}
	}
}

void Game::checkEnemiesPlayerCollision()
{
	for (int j = ZERO; j < (int)enemies.size(); j++) {
		if (SDL_HasIntersection(&enemies[j]->getTexture().getRenderQuad(), &player->getBounds())) {
			if (!player->isInvulnerable) {
				// Vibrates the controller
				if (SDL_HapticRumblePlay(controllerHaptic, RUMBLE_DEATH_STRENGTH, RUMBLE_DEATH_LENGTH) != ZERO) {
					SDL_Log("Warning: Unable to play rumble! %s\n", SDL_GetError());
				}
				// Erases the player's projectiles
				player->playerProjectiles.clear();

				// Sets the player as dead
				playerDeathTick = SDL_GetTicks();
				player->isAlive = player->isAllowedToShot = false;
				// Destroys the enemy
				enemies[j]->~Enemy();
				enemies.erase(enemies.begin() + j);
			}
		}
	}
}

// Checks the status of the player and modify the game accordingly
void Game::checkPlayerStatus()
{
	if (!player->isAlive && (int)SDL_GetTicks() >= playerDeathTick + PLAYER_RESPAWN_DELAY) {
		Mix_PlayChannel(-1, soundEffectPlayerExplosion, 0);
		removeLife();
		playerInvulnerabilityTick = SDL_GetTicks();
		player->destroySpaceShip();
	}
	else if (player->isInvulnerable && (int)SDL_GetTicks() >= playerInvulnerabilityTick + PLAYER_INVULNERABILITY_DELAY) {
		Mix_PlayChannel(-1, soundEffectPlayerRespawn, 0);
		player->respawn();
	}

	if (player->lives <= ZERO) {
		isLost = true;
		enemies.clear();
		player->playerProjectiles.clear();
		changeMusic(score <= bestScore ? MUSIC_LOST_GAME : MUSIC_LOST_GAME_BEST_SCORE);
	}

	if (player->isAllowedToShot && player->isShooting && (int)SDL_GetTicks() > player->shootDelayTick + PLAYER_SHOOT_DELAY) {
		Mix_PlayChannel(-1, soundEffectPlayerShoot, 0);
	}
}

/// TODO Prepare the enemies hordes generation
void Game::generateRandomPingPongEnemies()
{
	switch (Utils::getRandomInt(1, 2))
	{
	case 1:
		for (int i = 0; i < Utils::getRandomInt(8, 12); i++) {
			enemies.push_back(new PingpongEnemy((i + 1) * Utils::getRandomInt(120, 180), 1, "Images/ping.png", MULTIPLIER_FULL, renderer));
		}
		break;
	case 2:
		for (int i = 0; i < Utils::getRandomInt(1, 5); i++) {
			enemies.push_back(new FollowerEnemy(this, (i + 1) * Utils::getRandomInt(120, 180), levelHeight - 80, "Images/Follower64.png", MULTIPLIER_FULL, renderer));
		}
	default:
		break;
	}
}

// Handle the input events
void Game::manageEvent(SDL_Event * gameEvent)
{
	const Uint8* states = SDL_GetKeyboardState(NULL);

	// Quit the game by pressing ESCAPE
	if (states[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	// Press Start actions according to the current scene
	if ((int)SDL_GetTicks() >= pauseTick + PAUSE_DELAY && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) || states[SDL_SCANCODE_RETURN])) {
		switch (scene)
		{
		case S_GAME:
			if (!isLost) {
				isPaused = !isPaused;
				isPaused ? Mix_PauseMusic() : Mix_ResumeMusic();
			}
			else {
				resetGame();
				changeMusic(MUSIC_LEVEL_01);
			}
			break;
		case S_MANUAL:
			break;
		case S_HOME:
			switch (spriteMenuPosition)
			{
			case M_START:
				scene = S_GAME;
				changeMusic(MUSIC_LEVEL_01);
				break;
			case M_MANUAL:
				scene = S_MANUAL;
				changeMusic(MUSIC_CREDITS);
				break;
			case M_EXIT:
				isRunning = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		pauseTick = SDL_GetTicks();
	}

	// Press Back actions according to the current scene
	if ((int)SDL_GetTicks() >= pauseTick + PAUSE_DELAY && (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK) || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) || states[SDL_SCANCODE_BACKSPACE])) {
		switch (scene)
		{
		case S_GAME:
			if (isPaused || isLost) {
				changeMusic(MUSIC_HOME);
				scene = S_HOME;
				resetGame();
			}
			break;
		case S_MANUAL:
			changeMusic(MUSIC_HOME);
			scene = S_HOME;
			break;
		case S_HOME:
			break;
		default:
			break;
		}
	}

	// Controller axises actions according to the current scene
	if (gameEvent->type == SDL_CONTROLLERAXISMOTION || gameEvent->type == SDL_KEYDOWN)
	{
		switch (scene)
		{
		case S_HOME:
			if ((int)SDL_GetTicks() >= spriteMenuTick + SPRITES_DELAY) {
				if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -JOYSTICK_DEAD_ZONE || states[SDL_SCANCODE_W] || states[SDL_SCANCODE_Z]) {
					if (spriteMenuPosition >= ONE) {
						spriteMenuPosition--;
						Mix_PlayChannel(-1, soundEffectMenuMove, 0);
					}
				}
				else if (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > JOYSTICK_DEAD_ZONE || states[SDL_SCANCODE_S]) {
					if (spriteMenuPosition < MENU_ITEMS) {
						spriteMenuPosition++;
						Mix_PlayChannel(-1, soundEffectMenuMove, 0);
					}
				}
				spriteMenuTick = (int)SDL_GetTicks();
			}

			break;
		case S_MANUAL:
			break;
		case S_GAME:
			if (!isPaused && !isLost) {
				player->manageRightAxis(controller);
				player->manageLeftAxis(controller, windowWidth, windowHeight);
			}
			break;
		default:
			break;
		}
	}
	else {
		player->isShooting = false;
	}

	// Check collisions
	if (scene == S_GAME && !isLost && !isPaused) {
		checkEnemiesPlayerCollision();
		checkEnemiesPlayerBeamCollision();
		checkPlayerStatus();
	}

	if (isLost) {
		std::string lostResultText;
		if (score <= bestScore) {
			lostResultText = "You didn't beat the best score (" + std::to_string(bestScore) + ")";
		}
		else {
			lostResultText = "Congratulations : you beat the previous best score.";
			setBestScore("Texts/bestscore.txt", score);
		}

		setTextTexture(&resultTexture, lostResultText, fontSize);
	}
}

// Updates the position and state of the object according to the current scene
void Game::updateModel()
{
	switch (scene)
	{
	case S_HOME:
		switch (spriteMenuPosition)
		{
		case M_START:
			placeSprite(&buttonPlayTexture);
			break;
		case M_MANUAL:
			placeSprite(&buttonManualTexture);
			break;
		case M_EXIT:
			placeSprite(&buttonExitTexture);
			break;
		default:
			break;
		}

		spriteRectangle = { spriteX, spriteY, clips[ZERO].w , clips[ZERO].h };
		if ((int)SDL_GetTicks() > spriteTick + SPRITES_DELAY) {
			if (spriteCmp < SPRITES_COLUMNS * SPRITES_LINES - ONE) {
				spriteCmp++;
			}
			else {
				spriteCmp = ZERO;
			}
			spriteTick = SDL_GetTicks();
		}

		break;
	case M_MANUAL:
		break;
	case S_GAME:
		if (!isLost && !isPaused) {
			for (auto e : enemies) {
				e->EnemyMovement(levelWidth, levelHeight);
			}

			player->setOrientation();
			player->shot(renderer);
			player->setProjectiles();

			camera->x = player->getXPos() * (levelWidth / windowWidth);
			camera->y = player->getYPos() * (levelHeight / windowHeight);

			if (camera->x < ZERO) {
				camera->x = ZERO;
			}
			if (camera->y < ZERO) {
				camera->y = ZERO;
			}
			if (camera->x > levelWidth - camera->w) {
				camera->x = levelWidth - camera->w;
			}
			if (camera->y > levelHeight - camera->h) {
				camera->y = levelHeight - camera->h;
			}

			if ((int)(SDL_GetTicks() % 2000) < 10) {
				generateRandomPingPongEnemies();
			}
		}

		textScore = "Score : " + std::to_string(score);
		setTextTexture(&scoreTexture, textScore, (int)(windowHeight * MULTIPLIER_FONT));
		break;
	default:
		break;
	}
}

// Renders the object according to the current scene
void Game::drawModel()
{
	switch (scene)
	{
	case S_HOME:
		titleTexture.render((int)(windowWidth * MULTIPLIER_HALF - titleTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_QUARTER - titleTexture.getHeight() * MULTIPLIER_HALF), renderer);

		buttonPlayTexture.render((int)(windowWidth * MULTIPLIER_HALF - buttonPlayTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_HALF), renderer);
		buttonManualTexture.render((int)(windowWidth * MULTIPLIER_HALF - buttonPlayTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_HALF + (buttonPlayTexture.getHeight() + MARGIN) * M_MANUAL), renderer);
		buttonExitTexture.render((int)(windowWidth * MULTIPLIER_HALF - buttonPlayTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_HALF + (buttonPlayTexture.getHeight() + MARGIN) * M_EXIT), renderer);

		SDL_RenderCopyEx(renderer, spriteArrow, &clips[spriteCmp], &spriteRectangle, -RIGHT_ANGLE, NULL, SDL_FLIP_NONE);
		break;
	case M_MANUAL:
		titleTexture.render((int)(windowWidth * MULTIPLIER_HALF - titleTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_QUARTER - titleTexture.getHeight() * MULTIPLIER_HALF), renderer);

		for (int i = ZERO; i < (int)manualText.size(); i++) {
			manualText[i]->render((int)(windowWidth * MULTIPLIER_HALF - manualText[i]->getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_QUARTER + titleTexture.getHeight() + (manualText[i]->getHeight() + MARGIN) * i + ONE), renderer);
		}
		break;
	case S_GAME:
		bgTexture.render(ZERO, ZERO, renderer, camera);

		if (!isLost && !isPaused) {
			for (auto e : enemies) {
				e->render(renderer, camera->x, camera->y);
			}

			player->renderProjectiles(renderer);

			if (player->isAlive) {
				player->render(renderer);
			}
			else {
				if ((int)SDL_GetTicks() >= playerDeathTick + PLAYER_RESPAWN_DELAY) {
					player->isAlive = player->isInvulnerable = true;
					player->isAllowedToShot = false;
				}
			}
		}

		scoreTexture.render((int)((windowWidth - scoreTexture.getWidth()) * MULTIPLIER_HALF), ZERO, renderer);
		if (isPaused) {
			for (int i = ZERO; i < (int)pauseText.size(); i++) {
				pauseText[i]->render((int)(windowWidth * MULTIPLIER_HALF - pauseText[i]->getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_QUARTER + titleTexture.getHeight() + (pauseText[i]->getHeight() + MARGIN) * i + ONE), renderer);
			}
		}

		for (auto l : lives) {
			l->render(renderer);
		}

		if (isLost) {
			gameOverTexture.render((int)(windowWidth * MULTIPLIER_HALF - gameOverTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_QUARTER), renderer);
			resultTexture.render((int)(windowWidth * MULTIPLIER_HALF - resultTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_HALF), renderer);
			quitOrderTexture.render((int)(windowWidth * MULTIPLIER_HALF - quitOrderTexture.getWidth() * MULTIPLIER_HALF), (int)(windowHeight * MULTIPLIER_HALF + resultTexture.getHeight() + MARGIN), renderer);
		}
		break;
	default:
		break;
	}
}

void Game::updateView()
{
	SDL_RenderPresent(renderer);
}

void Game::erase()
{
	SDL_SetRenderDrawColor(renderer, clearColor[0], clearColor[1], clearColor[2], COLOR_MAX);
	SDL_RenderClear(renderer);
}

Player* Game::getPlayer()
{
	return player;
}

SDL_Rect Game::getCamera()
{
	return *camera;
}

int Game::getWindowWidth()
{
	return windowWidth;
}

int Game::getWindowHeight()
{
	return windowHeight;
}