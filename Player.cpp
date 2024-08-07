#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Player.h"
#include "InputFunctions.h"

bool Player::move(const Direction dir)
{
	if (m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir)) == nullptr)
	{
		std::cout << "Туда нельзя идти.\n";

		return false;
	}
	else if (m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir))->
		isRoomLocked(getOppositeDirection(dir)))
	{
		std::cout << "Дверь заперта. Туда нельзя идти.\n";

		return false;
	}
	else if (m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir)) != nullptr)
	{
		m_currentRoom = m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(dir));
		describeRoom();

		return true;
	}

	return false;
}

void Player::describeRoom() const
{
	std::cout << *m_currentRoom << '\n';
}

void Player::describeItemFromInventory(const std::vector<Item*>& itemList) const
{
	int choice{ getInventoryInput(itemList.size()) };

	if (choice == 0)
		return;

	std::cout << itemList.at(static_cast<std::size_t>(choice - 1))->getInspectionDescription() << '\n';
}

void Player::printInventory() const
{
	if (m_inventory.empty())
		std::cout << "В вашем инвентаре сейчас ничего нет.\n";
	else
	{
		std::cout << "В вашем инвентаре сейчас:\n";

		std::vector<Item*> itemList{};

		for (const auto& item : m_inventory)
			itemList.push_back(item.second);

		for (std::size_t item{ 0 }; item < itemList.size(); ++item)
			std::cout << item + 1 << ". " << itemList.at(item)->getName() << '\n';

		describeItemFromInventory(itemList);
	}
}

void Player::getItem(std::string_view itemName, const std::unordered_map<std::string_view, std::unique_ptr<Item>>& itemMap)
{
	if (m_currentRoom->getItemPtr())
	{
		auto itemFromKeyword{ std::find(m_currentRoom->getItemPtr()->getKeywords().begin(),
		   m_currentRoom->getItemPtr()->getKeywords().end(), itemName) };
		if (itemFromKeyword != m_currentRoom->getItemPtr()->getKeywords().end())
		{
			for (const auto& i : itemMap)
			{
				if (i.second.get() == m_currentRoom->getItemPtr())
					m_inventory.insert(std::make_pair(i.first, i.second.get()));
			}
			m_currentRoom->deleteItem();

			std::cout << "Вы подобрали: " << prev(m_inventory.end())->second->getName() << ".\n";

			return;
		}
	}

	std::cout << "Здесь нет " << itemName << ".\n";

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
		std::cout << "Вы открыли дверь.\n";
	}
	else if (room && room->isRoomLocked(dir))
		std::cout << "У вас нет предметов, которые могли бы открыть эту дверь.\n";
	else if (room)
		std::cout << "В этой стороне нет закрытых дверей\n";
	else
		std::cout << "В этой стороне нет дверей.\n";
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
		std::cout << "Рядом нет закрытых дверей.\n";
	else if (lockedDoorDirections.size() == 1)
		checkAndOpenDoor(m_currentRoom->getAdjacentRooms().at(static_cast<std::size_t>(lockedDoorDirections.at(0))), 
			getOppositeDirection(lockedDoorDirections.at(0)));
	else
	{
		std::cout << "Закрытые двери есть на ";
		for (const auto& i : lockedDoorDirections)
		{
			switch (i)
			{
			using enum Direction;
			case (north):	{ std::cout << "Севере "; break; }
			case (east):	{ std::cout << "Востоке "; break; }
			case (south):	{ std::cout << "Юге "; break; }
			case (west):	{ std::cout << "Западе "; break; }
			default:		assert("unknown locked door direction found");
			}
		}

		std::cout << "\nДверь в каком направлении вы хотите открыть? ";
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

	std::cout << "Не знаю, что значит открыть " << objectToOpen << ".\n";
}

void Player::inspectSomething(std::string_view objectToInspect) const
{
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

	// TODO: make this function work with polymorphism

	std::cout << "Здесь нет " << objectToInspect << ".\n";
}