#ifndef INPUT_FUNCTIONS_H
#define INPUT_FUNCTIONS_H
#include <utility>
#include <string>

constexpr int toLowerRus(char r)
{
	switch (r)
	{
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	case '�': r = '�'; break;
	}
	return (r);
}

bool inputValidation();
bool inputValidationNum();

int getInventoryInput(const std::size_t inventorySize);

Direction getDirectionInput();

std::pair<std::string, std::string> getActionsInput();

#endif