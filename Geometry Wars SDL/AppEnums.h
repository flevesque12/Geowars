#pragma once

#ifndef APPENUMS_H
#define APPENUMS_H

// Directions used to move the objects
enum EDirections {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Axis of the controller
enum EAxis {
	NEGATIVE = -1,
	NEUTRAL = 0,
	POSITIVE = 1
};

// Scenes of the game
enum EScenes {
	S_GAME,
	S_MANUAL,
	S_HOME
};

// Menu options
enum EMenu {
	M_START,
	M_MANUAL,
	M_EXIT
};

// Constructor
class AppEnums
{
};

#endif // !1
