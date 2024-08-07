#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Player.h"
#include "InputFunctions.h"

void Player::move(const Direction dir)
{
	if (!m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir)))
	{
		std::cout << "���� ������ ����.\n";
	}
	else if (m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir))->
		isRoomLocked(getOppositeDirection(dir)))
	{
		std::cout << "����� �������. ���� ������ ����.\n";
	}
	else if (m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir)))
	{
		m_currentRoom = m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir));
		describeRoom();
	}
}

void Player::teleport(Room* room)
{
	if (room)
		m_currentRoom = room;
	else
		assert("couldn't teleport, room doesn't exist");
}

void Player::describeRoom() const
{
	std::cout << *m_currentRoom << '\n';
}

void Player::describeItemFromInventory(const std::vector<Object*>& itemList) const
{
	int choice{ getInventoryInput(itemList.size()) };

	if (choice == 0)
		return;

	std::cout << itemList.at(static_cast<std::size_t>(choice - 1))->getInspectionDescription() << '\n';
}

void Player::printInventory() const
{
	if (m_inventory.empty())
		std::cout << "� ����� ��������� ������ ������ ���.\n";
	else
	{
		std::cout << "� ����� ��������� ������:\n";

		std::vector<Object*> itemList{};

		for (const auto& item : m_inventory)
			itemList.push_back(item.second);

		for (std::size_t item{ 0 }; item < itemList.size(); ++item)
			std::cout << item + 1 << ". " << itemList.at(item)->getName() << '\n';

		describeItemFromInventory(itemList);
	}
}

void Player::takeItem(std::string_view itemName)
{
	// First checks for regular objects
	for (const auto& object : m_currentRoom->getObjects())
	{
		auto objectFromKeyword{ std::find(object->getKeywords().begin(), object->getKeywords().end(), itemName) };
		if ((objectFromKeyword != object->getKeywords().end()) && (object->canPickUp()))
		{
			m_inventory.insert(std::make_pair(object->getName(), object));

			m_currentRoom->deleteObject(object);

			std::cout << "�� ���������: " << prev(m_inventory.end())->second->getName() << ".\n";

			return;
		}
		else if (objectFromKeyword != object->getKeywords().end())
		{
			std::cout << "��� �� ����� ����� � ����� " << itemName << ".\n";

			return;
		}
	}

	// Then checks for simple objects
	for (const auto& object : m_currentRoom->getSimpleObjects())
	{
		auto objectFromKeyword{ std::find(object.getKeywords().begin(), object.getKeywords().end(), itemName) };
		if (objectFromKeyword != object.getKeywords().end())
		{
			std::cout << "��� �� ����� ����� � ����� " << itemName << ".\n";

			return;
		}
	}

	std::cout << "����� ��� " << itemName << ".\n";
}

bool Player::ifItemInInventory(Item* itemToCheck) const
{
	auto itemInInventory{ m_inventory.find(itemToCheck->getName()) };

	return (itemInInventory != m_inventory.end());
}

void Player::checkAndOpenDoor(Room* room, const Direction dir) const
{
	if (room && room->isRoomLocked(dir) && room->getItemToOpenDoorPtr(dir) &&
		ifItemInInventory(room->getItemToOpenDoorPtr(dir)))
	{
		room->openRoom(dir);
		std::cout << "�� ������� �����.\n";
	}
	else if (room && room->isRoomLocked(dir))
		std::cout << "� ��� ��� ���������, ������� ����� �� ������� ��� �����.\n";
	else if (room)
		std::cout << "� ���� ������� ��� �������� ������\n";
	else
		std::cout << "� ���� ������� ��� ������.\n";
}

void Player::openDoorLogic() const
{
	std::vector<Direction> lockedDoorDirections{};

	for (Direction direction{ Direction::north }; static_cast<std::size_t>(direction) <
		m_currentRoom->getAdjacentRooms().size(); direction = static_cast<Direction>(static_cast<int>(direction) + 1))
	{
		if (m_currentRoom->getAdjacentRooms()[static_cast<std::size_t>(direction)] &&
			m_currentRoom->getAdjacentRooms()[static_cast<std::size_t>(direction)]->isRoomLocked(getOppositeDirection(direction)))
			lockedDoorDirections.push_back(direction);
	}

	if (lockedDoorDirections.size() == 0)
		std::cout << "����� ��� �������� ������.\n";
	else if (lockedDoorDirections.size() == 1)
		checkAndOpenDoor(m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(lockedDoorDirections.at(0))), 
			getOppositeDirection(lockedDoorDirections.at(0)));
	else
	{
		std::cout << "�������� ����� ���� ��: [";
		for (const auto& i : lockedDoorDirections)
			std::cout << getStringFromDirection(i) << "� ";

		std::cout << "\b]\n����� � ����� ����������� �� ������ �������? ";
		Direction inputDirection{ getDirectionInput() };

		checkAndOpenDoor(m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(inputDirection)),
			getOppositeDirection(inputDirection));
	}
}

void Player::openSomething(std::string_view objectToOpen) const
{
	auto objectToOpenFromKeyword{ m_objectsToOpen.find(static_cast<std::string>(objectToOpen))};
	if (objectToOpenFromKeyword != m_objectsToOpen.end())
	{
		switch (objectToOpenFromKeyword->second)
		{
		case (ObjectToOpen::door): { openDoorLogic();  return; }
		}
	}

	std::cout << "�� ����, ��� ������ ������� " << objectToOpen << ".\n";
}

void Player::inspectSomething(std::string_view objectToInspect) const
{
	// Checks simple objects for inspection first
	bool simpleObjectFound{ false };
	std::size_t simpleObjectIndex{0};
	for (std::size_t i{ 0 }; i < m_currentRoom->getSimpleObjects().size(); ++i)
	{
		if (std::find(m_currentRoom->getSimpleObjects().at(i).getKeywords().begin(), 
			m_currentRoom->getSimpleObjects().at(i).getKeywords().end(), objectToInspect) !=
			m_currentRoom->getSimpleObjects().at(i).getKeywords().end())
		{
			simpleObjectIndex = i;
			simpleObjectFound = true;
			break;
		}
	}

	if (simpleObjectFound)
	{
		std::cout << m_currentRoom->getSimpleObjects().at(simpleObjectIndex).getInspectionDescription() << '\n';
		return;
	}

	// Check if the player tried to inspect a door that doesn't exist as a simple object.
	// Returns the same message for all doors.
	// No need to inspect other openable objects here as they are regular objects
	auto doorCheck{ m_objectsToOpen.find(objectToInspect) };
	if ((doorCheck != m_objectsToOpen.end()) && (doorCheck->second == door))
	{
		std::cout << "�� ���� ������ ����������.\n";
		return;
	}

	// Then checks for regular objects
	bool objectFound{ false };
	std::size_t objectIndex{ 0 };
	for (std::size_t i{ 0 }; i < m_currentRoom->getObjects().size(); ++i)
	{
		if (std::find(m_currentRoom->getObjects().at(i)->getKeywords().begin(),
			m_currentRoom->getObjects().at(i)->getKeywords().end(), objectToInspect) !=
			m_currentRoom->getObjects().at(i)->getKeywords().end())
		{
			objectIndex = i;
			objectFound = true;
			break;
		}
	}

	if (objectFound)
	{
		std::cout << m_currentRoom->getObjects().at(simpleObjectIndex)->getInspectionDescription() << '\n';
		return;
	}

	std::cout << "����� ��� " << objectToInspect << ".\n";
}

void Player::useSomething(std::string_view objectToUse) const
{
	// First checks for regular objects
	for (const auto& object : m_currentRoom->getObjects())
	{
		auto objectFromKeyword{ std::find(object->getKeywords().begin(), object->getKeywords().end(), objectToUse) };
		if ((objectFromKeyword != object->getKeywords().end()) && (object->canActivate()))
		{
			object->activate();

			return;
		}
		else if (objectFromKeyword != object->getKeywords().end())
		{
			std::cout << "� �� ���� ������������ " << objectToUse << ".\n";

			return;
		}
	}

	// Then checks for simple objects
	for (const auto& object : m_currentRoom->getSimpleObjects())
	{
		auto objectFromKeyword{ std::find(object.getKeywords().begin(), object.getKeywords().end(), objectToUse) };
		if (objectFromKeyword != object.getKeywords().end())
		{
			std::cout << "� �� ���� ������������ " << objectToUse << ".\n";

			return;
		}
	}

	std::cout << "����� ��� " << objectToUse << ".\n";
}

void Player::restHere()
{
	if (!m_currentRoom->getIsSafeRoom())
		std::cout << "�� �� ���������� ���� ���������� ���������, ����� �������� �����.\n";
	else
	{
		m_checkpointRoom = m_currentRoom;

		std::cout << "�� �������������� � ������� ������� ���������.\n"
			<< "������ �� ������ ��������� (���������) � ��� �������.\n";
	}
}

void Player::goBack()
{
	if (!m_checkpointRoom)
		std::cout << "�� ��� �� �������� � ���������� �����, ����� ����� ���� ���������.\n";
	else if (m_checkpointRoom == m_currentRoom)
		std::cout << "�� ��� � �������, � ������� �������� ��������� ���.\n";
	else
	{
		std::cout << "�� ������������� � �������, � ������� ��������� ��� ��������.\n";

		teleport(m_checkpointRoom);
	}
}