#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <string_view>
#include <unordered_map>
#include <memory>

#include "Room.h"
#include "Player.h"
#include "TypeAliases.h"

void gameLoop(const Maps::ItemMap& itemMap, Player& player);
#endif