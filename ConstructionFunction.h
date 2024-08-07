#ifndef CONSTRUCTION_FUNCTION_H
#define CONSTRUCTION_FUNCTION_H

#include <iostream>
#include <unordered_map>

#include "Item.h"
#include "Room.h"
#include "TypeAliases.h"

Maps::RoomMap constructRoomMap();

Maps::ObjectMap constructObjects(const Maps::RoomMap& roomMap);

void populateRooms(Maps::RoomMap& roomMap, const Maps::ObjectMap& objectMap);
#endif