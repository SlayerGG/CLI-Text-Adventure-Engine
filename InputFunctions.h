#ifndef INPUT_FUNCTIONS_H
#define INPUT_FUNCTIONS_H
#include <utility>
#include <string>

constexpr int toLowerRus(char r)
{
	switch (r)
	{
	case 'À': r = 'à'; break;
	case 'Á': r = 'á'; break;
	case 'Â': r = 'â'; break;
	case 'Ã': r = 'ã'; break;
	case 'Ä': r = 'ä'; break;
	case 'Å': r = 'å'; break;
	case '¨': r = '¸'; break;
	case 'Æ': r = 'æ'; break;
	case 'Ç': r = 'ç'; break;
	case 'È': r = 'è'; break;
	case 'É': r = 'é'; break;
	case 'Ê': r = 'ê'; break;
	case 'Ë': r = 'ë'; break;
	case 'Ì': r = 'ì'; break;
	case 'Í': r = 'í'; break;
	case 'Î': r = 'î'; break;
	case 'Ï': r = 'ï'; break;
	case 'Ð': r = 'ð'; break;
	case 'Ñ': r = 'ñ'; break;
	case 'Ò': r = 'ò'; break;
	case 'Ó': r = 'ó'; break;
	case 'Ô': r = 'ô'; break;
	case 'Õ': r = 'õ'; break;
	case 'Ö': r = 'ö'; break;
	case '×': r = '÷'; break;
	case 'Ø': r = 'ø'; break;
	case 'Ù': r = 'ù'; break;
	case 'Ú': r = 'ú'; break;
	case 'Û': r = 'û'; break;
	case 'Ü': r = 'ü'; break;
	case 'Ý': r = 'ý'; break;
	case 'Þ': r = 'þ'; break;
	case 'ß': r = 'ÿ'; break;
	}
	return (r);
}

bool inputValidation();
bool inputValidationNum();

int getInventoryInput(const std::size_t inventorySize);

Direction getDirectionInput();

std::pair<std::string, std::string> getActionsInput();

#endif