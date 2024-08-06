#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <string_view>
#include <vector>

#include "Object.h"

class Item : public Object
{
public:
	Item(std::string_view name, std::string_view inRoomDescription,
		std::string_view inspectionDescription, std::vector<std::string> keywords) : 
		Object{name, inRoomDescription, inspectionDescription, keywords}
	{
	}
};
#endif