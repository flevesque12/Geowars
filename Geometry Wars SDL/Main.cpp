#include "Game.h"

using namespace std;

int main(int argc, char * argv[])
{
	int result = 0;
	Game* g = new Game();
	result = g->initialize();

	if (result == 0) {
		g->execute();
	}
	g->freeMemory();

	return result;
}