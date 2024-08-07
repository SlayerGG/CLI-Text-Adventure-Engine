#include <memory>
#include <unordered_map>
#include <utility>

#include "Object.h"
#include "Item.h"
#include "Room.h"
#include "TypeAliases.h"

Maps::ItemMap constructItems()
{
	auto keycardToDockingControls{ std::make_unique<Item>("Ключ-карта к комнате управления ангаром", "На столе лежит ключ-карта.",
		"Это ключ-карта от комнаты управления ангаром",
		std::vector<std::string>{"карта", "карту", "ключ-карта", "ключ-карту"}) };

	auto keycardToStorageRoom{ std::make_unique<Item>("Ключ-карта к складскому помещению", "На столе лежит ключ-карта.",
		"Это ключ-карта от складского помещения",
		std::vector<std::string>{"карта", "карту", "ключ-карта", "ключ-карту"}) };

	Maps::ItemMap itemMap{};

	itemMap.insert(std::make_pair(keycardToDockingControls->getName(), std::move(keycardToDockingControls)));
	itemMap.insert(std::make_pair(keycardToStorageRoom->getName(), std::move(keycardToStorageRoom)));

	return itemMap;
}

// Game map in a chart form can be found in "Map chart.drawio"
Maps::RoomMap constructGameMap(const Maps::ItemMap& itemMap)
{
	auto dockingBay{ std::make_unique<Room>("Это стыковочный отсек.") };
	auto corridor1{ std::make_unique<Room>("Это коридор 1.") };
	auto bayControls{ std::make_unique<Room>("Это комната управления стыковочным отсеком.") };
	auto storageRoom{ std::make_unique<Room>("Это склад.") };
	auto corridor2{ std::make_unique<Room>("Это коридор 2.") };
	auto galley{ std::make_unique<Room>("Это столовая.") };

	// Linking block
	dockingBay->linkAdjacentRoom(corridor1.get(), Direction::north);
	corridor1->linkAdjacentRoom(bayControls.get(), Direction::west);
	corridor1->linkAdjacentRoom(corridor2.get(), Direction::north);
	corridor1->linkAdjacentRoom(storageRoom.get(), Direction::east);
	corridor2->linkAdjacentRoom(galley.get(), Direction::west);
	bayControls->linkAdjacentRoom(galley.get(), Direction::north);

	// Room manipulation block
	bayControls->lockRoomBi(Direction::east, itemMap.at("Ключ-карта к комнате управления ангаром").get())
		.insertItem(itemMap.at("Ключ-карта к складскому помещению").get());
	storageRoom->lockRoomBi(Direction::west, itemMap.at("Ключ-карта к складскому помещению").get());
	Object table{ "Стол", "", "Обычный стальной стол.", std::vector<std::string>{"стол"} };
	corridor2->insertSimpleObject(table).insertItem(itemMap.at("Ключ-карта к комнате управления ангаром").get());

	Maps::RoomMap gameMap{};

	// map insertion block
	gameMap.insert(std::make_pair("Docking bay", std::move(dockingBay)));
	gameMap.insert(std::make_pair("Corridor 1", std::move(corridor1)));
	gameMap.insert(std::make_pair("Bay controls", std::move(bayControls)));
	gameMap.insert(std::make_pair("Corridor 2", std::move(corridor2)));
	gameMap.insert(std::make_pair("Storage room", std::move(storageRoom)));
	gameMap.insert(std::make_pair("Galley", std::move(galley)));

	return gameMap;
}