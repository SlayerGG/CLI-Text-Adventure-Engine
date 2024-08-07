#ifndef  TYPE_ALIASES_H
#define TYPE_ALIASES_H

#include <unordered_map>
#include <string_view>
#include <memory>

#include "Item.h"
#include "Room.h"
#include "Player.h"

namespace Maps
{
	using ObjectMap = std::unordered_map<std::string_view, std::unique_ptr<Object>>;
	using RoomMap = std::unordered_map<std::string_view, std::unique_ptr<Room>>;
}

#endif // ! TYPE_ALIASES_H