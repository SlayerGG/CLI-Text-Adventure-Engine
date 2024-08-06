#ifndef MAP_TYPE_ALIASES_H
#define MAP_TYPE_ALIASES_H
#include <unordered_map>
#include <string>
#include <memory>

#include "Item.h"
#include "Room.h"
#include "Player.h"

using ItemMap = std::unordered_map<std::string_view, std::unique_ptr<Item>>;
using RoomMap = std::unordered_map<std::string_view, std::unique_ptr<Room>>;
using ActionMap = std::unordered_map<std::string, Player::Action>;
using ObjectToOpenMap = std::unordered_map<std::string, Player::ObjectToOpen>;
#endif