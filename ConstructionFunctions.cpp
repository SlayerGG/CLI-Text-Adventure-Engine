#include <memory>
#include <unordered_map>
#include <utility>

#include "Object.h"
#include "Item.h"
#include "Room.h"
#include "TypeAliases.h"

Maps::ItemMap constructItems()
{
	auto keycardToDockingControls{ std::make_unique<Item>("����-����� � ������� ���������� �������", "�� ����� ����� ����-�����.",
		"��� ����-����� �� ������� ���������� �������",
		std::vector<std::string>{"�����", "�����", "����-�����", "����-�����"}) };

	auto keycardToStorageRoom{ std::make_unique<Item>("����-����� � ���������� ���������", "�� ����� ����� ����-�����.",
		"��� ����-����� �� ���������� ���������",
		std::vector<std::string>{"�����", "�����", "����-�����", "����-�����"}) };

	Maps::ItemMap itemMap{};

	itemMap.insert(std::make_pair(keycardToDockingControls->getName(), std::move(keycardToDockingControls)));
	itemMap.insert(std::make_pair(keycardToStorageRoom->getName(), std::move(keycardToStorageRoom)));

	return itemMap;
}

// Game map in a chart form can be found in "Map chart.drawio"
Maps::RoomMap constructGameMap(const Maps::ItemMap& itemMap)
{
	auto dockingBay{ std::make_unique<Room>("��� ����������� �����.") };
	auto corridor1{ std::make_unique<Room>("��� ������� 1.") };
	auto bayControls{ std::make_unique<Room>("��� ������� ���������� ����������� �������.") };
	auto storageRoom{ std::make_unique<Room>("��� �����.") };
	auto corridor2{ std::make_unique<Room>("��� ������� 2.") };
	auto galley{ std::make_unique<Room>("��� ��������.") };

	// Linking block
	dockingBay->linkAdjacentRoom(corridor1.get(), Direction::north);
	corridor1->linkAdjacentRoom(bayControls.get(), Direction::west);
	corridor1->linkAdjacentRoom(corridor2.get(), Direction::north);
	corridor1->linkAdjacentRoom(storageRoom.get(), Direction::east);
	corridor2->linkAdjacentRoom(galley.get(), Direction::west);
	bayControls->linkAdjacentRoom(galley.get(), Direction::north);

	// Room manipulation block
	bayControls->lockRoomBi(Direction::east, itemMap.at("����-����� � ������� ���������� �������").get())
		.insertItem(itemMap.at("����-����� � ���������� ���������").get());
	storageRoom->lockRoomBi(Direction::west, itemMap.at("����-����� � ���������� ���������").get());
	Object table{ "����", "", "������� �������� ����.", std::vector<std::string>{"����"} };
	corridor2->insertSimpleObject(table).insertItem(itemMap.at("����-����� � ������� ���������� �������").get());

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