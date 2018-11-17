#include "Utils.h"

double Utils::degToRad(double angleInDeg)
{
	return angleInDeg * (180.0f / M_PI);
}

int Utils::getRandomInt(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}

Utils::Utils()
{
}

Utils::~Utils()
{
}