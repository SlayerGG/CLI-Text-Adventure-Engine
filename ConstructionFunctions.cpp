#include <memory>
#include <unordered_map>
#include <utility>

#include "Object.h"
#include "Item.h"
#include "Room.h"
#include "Lever.h"
#include "TypeAliases.h"

// Game map in a chart form can be found in "Map chart.drawio"
Maps::RoomMap constructRoomMap()
{
	// Room creating block
	auto dockingBay{ std::make_unique<Room>("Стыковочный отсек", "Это стыковочный отсек.") };
	auto corridor1{ std::make_unique<Room>("Коридор 1", "Это коридор 1.") };
	auto corridor2{ std::make_unique<Room>("Коридор 2", "Это коридор 2.") };
	auto galley{ std::make_unique<Room>("Столовая", "Это столовая.") };
	auto bayControls{ std::make_unique<Room>("Комната управления стыковочным отсеком", "Это комната управления стыковочным отсеком.") };
	auto storageRoom{ std::make_unique<Room>("Склад", "Это склад.") };
	auto engineering{ std::make_unique<Room>("Инженерный отсек", "Вы оказались в затемнённой комнате, \
иногда освещаемой красным светом. Слышен гул работающей техники.\n\
В углу стоит компьютер. Рядом с ним стоит шкаф.") };

	// Linking block
	dockingBay->linkAdjacentRoom(corridor1.get(), Direction::north);
	corridor1->linkAdjacentRoom(bayControls.get(), Direction::west);
	corridor1->linkAdjacentRoom(corridor2.get(), Direction::north);
	corridor1->linkAdjacentRoom(storageRoom.get(), Direction::east);
	corridor2->linkAdjacentRoom(galley.get(), Direction::west);
	bayControls->linkAdjacentRoom(galley.get(), Direction::north);
	storageRoom->linkAdjacentRoom(engineering.get(), Direction::east);

	Maps::RoomMap roomMap{};

	// map insertion block
	roomMap.insert(std::make_pair(dockingBay->getName(), std::move(dockingBay)));
	roomMap.insert(std::make_pair(corridor1->getName(), std::move(corridor1)));
	roomMap.insert(std::make_pair(bayControls->getName(), std::move(bayControls)));
	roomMap.insert(std::make_pair(corridor2->getName(), std::move(corridor2)));
	roomMap.insert(std::make_pair(storageRoom->getName(), std::move(storageRoom)));
	roomMap.insert(std::make_pair(galley->getName(), std::move(galley)));
	roomMap.insert(std::make_pair(engineering->getName(), std::move(engineering)));

	return roomMap;
}

Maps::ObjectMap constructObjects(const Maps::RoomMap& roomMap)
{
	auto keycardToDockingControls{ std::make_unique<Item>("Ключ-карта к комнате управления ангаром", "На столе лежит ключ-карта.",
		"Это ключ-карта от комнаты управления ангаром",
		std::vector<std::string>{"карта", "карту", "ключ-карта", "ключ-карту"}) };

	auto leverToStorage{ std::make_unique<Lever>("Рычаг к складу", "На полу стоит большой рычаг.", "Обычный стальной рычаг.",
	std::vector<std::string>{"рычаг"}, "Вы потянули рычаг.\nНа востоке слышен звук открывающейся двери.",
		"Этот рычаг уже активирован. Он открыл что-то на востоке.",
		roomMap.at("Склад").get(), Direction::west)};

	Maps::ObjectMap objectMap{};

	objectMap.insert(std::make_pair(keycardToDockingControls->getName(), std::move(keycardToDockingControls)));
	objectMap.insert(std::make_pair(leverToStorage->getName(), std::move(leverToStorage)));

	return objectMap;
}

void populateRooms(Maps::RoomMap& roomMap, const Maps::ObjectMap& objectMap)
{
	roomMap.at("Комната управления стыковочным отсеком")->lockRoomBi(Direction::east, 
		dynamic_cast<Item*>(objectMap.at("Ключ-карта к комнате управления ангаром").get()))
		.insertObject(objectMap.at("Рычаг к складу").get());
	roomMap.at("Склад")->lockRoomBi(Direction::west);
	Object table{ "Стол", "", "Обычный стальной стол.", std::vector<std::string>{"стол"} };
	roomMap.at("Коридор 2")->insertSimpleObject(table).insertObject(objectMap.at("Ключ-карта к комнате управления ангаром").get());
	Object computer{ "Компьютер", "", "Компьютер выключен. Похоже, у него нет питания.", std::vector<std::string>{"компьютер"} };
	Object drawer{ "Шкаф", "", "Металлический шкаф с подсветкой вверху. Ящики закрыты. Вы не видите замка.",
	std::vector<std::string>{"шкаф"} };
	Object machinery{ "Техника", "", "Большие коробки и цилиндры с дверцами, внутри которых слышен гул. Дверцы закрыты.",
		std::vector<std::string>{"техника", "технику"} };
	roomMap.at("Инженерный отсек")->insertSimpleObject(computer).insertSimpleObject(drawer)
		.insertSimpleObject(machinery);
}