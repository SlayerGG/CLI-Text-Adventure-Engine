#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include "Direction.h"
#include "InputFunctions.h"

bool inputValidation()
{
	if(std::cin.fail()) // no extraction took place
	{
		if (std::cin.eof()) // If the stream was closed
		{
			exit(0); // Shut down the program now
		}

		std::cin.clear(); // reset the state bits back to goodbit so we can use ignore()
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear out the bad input from the stream
		return false; // try again
	}

	return true;
}

bool inputValidationNum()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear out any additional input from the stream

	if (std::cin.gcount() > 1) // if we cleared out more than one additional character
		return false; // we'll consider this input to be invalid

	return true;
}

int getInventoryInput(const std::size_t inventorySize)
{
	int choice{};

	while (true)
	{
		std::cout << "Введите цифру предмета, чтобы рассмотреть его (0 - выход): ";
		std::cin >> choice;

		if (!inputValidation() || !inputValidationNum() || (choice < 0 || choice > inventorySize))
			continue;

		break;
	}

	return choice;
}

Direction getDirectionInput()
{
	Direction direction{};
	while (true)
	{
		std::string input{};
		bool isValidInput{false};
		while (!isValidInput)
		{
			std::getline(std::cin, input);
			isValidInput = inputValidation();
		}
		std::transform(input.begin(), input.end(), input.begin(),
			[](char c) { return toLowerRus(c); });

		auto directionInMap{ DirectionMap::directionMap.find(input) };

		if (directionInMap != DirectionMap::directionMap.end())
		{
			direction = directionInMap->second;
			break;
		}
		else
			std::cout << "Я не знаю такого направления.\n";
	}

	return direction;
}

std::pair<std::string, std::string> getActionsInput()
{
	std::cout << "Что вы хотите сделать?: ";
	std::string input{};
	bool isValidInput{ false };
	while (!isValidInput)
	{
		std::getline(std::cin, input);
		isValidInput = inputValidation();
	}

	std::transform(input.begin(), input.end(), input.begin(),
		[](char c) { return toLowerRus(c); });

	// Input splitting block
	std::stringstream inputStream{ input };

	std::string word1{};
	std::string word2{};

	std::getline(inputStream, word1, ' ');
	std::getline(inputStream, word2, ' ');

	return std::make_pair(word1, word2);
}