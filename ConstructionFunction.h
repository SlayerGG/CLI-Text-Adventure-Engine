#ifndef CONSTRUCTION_FUNCTION_H
#define CONSTRUCTION_FUNCTION_H

#include <iostream>
#include <unordered_map>

#include "Item.h"
#include "Room.h"
#include "TypeAliases.h"

Maps::ItemMap constructItems();

Maps::RoomMap constructGameMap(const Maps::ItemMap& itemMap);
#endif