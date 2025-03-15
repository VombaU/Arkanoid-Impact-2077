#include "Game.h"
#include <random>

int main()
{
	srand(time(nullptr));
	Game* g = new Game();
	run(g);
	return 0;
}