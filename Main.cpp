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

	auto roomMap{ constructRoomMap() };

	auto objectMap{ constructObjects(roomMap) };

	populateRooms(roomMap, objectMap);

	Player player{ roomMap.at("Стыковочный отсек").get()};

	bool gameIsOver{ false };
	while (!gameIsOver)
	{
		gameLoop(player);
	}

	return 0;
}