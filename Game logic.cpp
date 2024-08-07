#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "Game logic.h"
#include "InputFunctions.h"
#include "Player.h"
#include "TypeAliases.h"

void takeAction(Player& player)
{
	std::pair<std::string, std::string> input{};

	Player::Action action{ Player::Action::unknownAction };

	while (action == Player::Action::unknownAction)
	{
		input = getActionsInput();

		if (player.getActions().find(input.first) != player.getActions().end())
			action = player.getActions().at(input.first);
		else
		{
			std::cout << "Извините, я не знаю такой команды.\n";
			continue;
		}
	}

	switch (action)
	{
		using enum Player::Action;
	case (north): { player.move(Direction::north); break; }
	case (east): { player.move(Direction::east); break; }
	case (south): { player.move(Direction::south); break; }
	case (west): { player.move(Direction::west); break; }
	case (look): { player.describeRoom(); break; }
	case (get): {
		if (!input.second.empty())
			player.getItem(input.second);
		else
			std::cout << "Взять что?\n";
		break;
	}
	case (inventory): { player.printInventory(); break; }
	case (open): {
		if (!input.second.empty())
			player.openSomething(input.second);
		else
			std::cout << "Открыть что?\n";
		break;
	}
	case (inspect): {
		if (!input.second.empty())
			player.inspectSomething(input.second);
		else
			std::cout << "Рассмотреть что?\n";
		break;
	}
	default: { std::cerr << "Unknown action passed\n"; }
	}
}

void gameLoop(Player& player)
{
	takeAction(player);

	return;
}