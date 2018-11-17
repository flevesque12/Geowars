#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "SDL.h"
#include "AppIncludes.h"

class Utils
{
public:
	static double degToRad(double angleInDeg);
	static int getRandomInt(int min, int max);
private:
	Utils();
	~Utils();
};

#endif // !UTILS_H
