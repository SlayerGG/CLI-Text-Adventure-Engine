#include <memory>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOCOMM 1
#define NOMINMAX 1
#include <Windows.h>

#include "Player.h"
#include "Game logic.h"
#include "ConstructionFunction.h"

int main()
{
	// Enable support of cyrillic
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto itemMap{ constructItems() };

	auto gameMap{ constructGameMap(itemMap) };

	Player player{ gameMap.at("Docking bay").get()};

	bool gameIsOver{ false };
	while (!gameIsOver)
	{
		gameLoop(itemMap, player);
	}

	return 0;
}