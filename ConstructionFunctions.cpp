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
	auto dockingBay{ std::make_unique<Room>("����������� �����", "��� ����������� �����.") };
	auto corridor1{ std::make_unique<Room>("������� 1", "��� ������� 1.") };
	auto corridor2{ std::make_unique<Room>("������� 2", "��� ������� 2.") };
	auto galley{ std::make_unique<Room>("��������", "��� ��������.") };
	auto bayControls{ std::make_unique<Room>("������� ���������� ����������� �������", "��� ������� ���������� ����������� �������.") };
	auto storageRoom{ std::make_unique<Room>("�����", "��� �����.") };
	auto engineering{ std::make_unique<Room>("���������� �����", "�� ��������� � ���������� �������, \
������ ���������� ������� ������. ������ ��� ���������� �������.\n\
� ���� ����� ���������. ����� � ��� ����� ����.") };

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
	auto keycardToDockingControls{ std::make_unique<Item>("����-����� � ������� ���������� �������", "�� ����� ����� ����-�����.",
		"��� ����-����� �� ������� ���������� �������",
		std::vector<std::string>{"�����", "�����", "����-�����", "����-�����"}) };

	auto leverToStorage{ std::make_unique<Lever>("����� � ������", "�� ���� ����� ������� �����.", "������� �������� �����.",
	std::vector<std::string>{"�����"}, "�� �������� �����.\n�� ������� ������ ���� ������������� �����.",
		"���� ����� ��� �����������. �� ������ ���-�� �� �������.",
		roomMap.at("�����").get(), Direction::west)};

	Maps::ObjectMap objectMap{};

	objectMap.insert(std::make_pair(keycardToDockingControls->getName(), std::move(keycardToDockingControls)));
	objectMap.insert(std::make_pair(leverToStorage->getName(), std::move(leverToStorage)));

	return objectMap;
}

void populateRooms(Maps::RoomMap& roomMap, const Maps::ObjectMap& objectMap)
{
	roomMap.at("������� ���������� ����������� �������")->lockRoomBi(Direction::east, 
		dynamic_cast<Item*>(objectMap.at("����-����� � ������� ���������� �������").get()))
		.insertObject(objectMap.at("����� � ������").get());
	roomMap.at("�����")->lockRoomBi(Direction::west);
	Object table{ "����", "", "������� �������� ����.", std::vector<std::string>{"����"} };
	roomMap.at("������� 2")->insertSimpleObject(table).insertObject(objectMap.at("����-����� � ������� ���������� �������").get());
	Object computer{ "���������", "", "��������� ��������. ������, � ���� ��� �������.", std::vector<std::string>{"���������"} };
	Object drawer{ "����", "", "������������� ���� � ���������� ������. ����� �������. �� �� ������ �����.",
	std::vector<std::string>{"����"} };
	Object machinery{ "�������", "", "������� ������� � �������� � ��������, ������ ������� ������ ���. ������ �������.",
		std::vector<std::string>{"�������", "�������"} };
	roomMap.at("���������� �����")->insertSimpleObject(computer).insertSimpleObject(drawer)
		.insertSimpleObject(machinery);
}