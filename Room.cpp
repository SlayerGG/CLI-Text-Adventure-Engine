#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "Direction.h"
#include "Room.h"
#include "Player.h"

Room& Room::insertSimpleObject(Object object)
{
	m_simpleObjects.push_back(std::move(object));

	return *this;
}

Room& Room::insertObject(Object* object)
{
	m_objects.push_back(object);

	return *this;
}

Room& Room::deleteObject(const Object* object)
{
	assert((std::find(m_objects.begin(), m_objects.end(), object) != m_objects.end()) &&
		"object to delete in room not found");

	std::erase(m_objects, object);

	return *this;
}

Room& Room::lockRoomUni(const Direction lockedRoomDirection, Item* itemToOpenDoor)
{
	m_lockedRoomDirectionsFlags |= getMaskFromDirection(lockedRoomDirection);

	m_itemToOpenDoor.at(static_cast<std::size_t>(lockedRoomDirection)) = itemToOpenDoor;

	return *this;
}

Room& Room::lockRoomBi(const Direction lockedRoomDirection, Item* itemToOpenDoor)
{
	assert(m_adjacentRooms.at(static_cast<std::size_t>(lockedRoomDirection)) &&
	"Room on the the other side of the locked door doesn't exist");

	lockRoomUni(lockedRoomDirection, itemToOpenDoor);

	m_adjacentRooms.at(static_cast<std::size_t>(lockedRoomDirection))->
		lockRoomUni(getOppositeDirection(lockedRoomDirection), itemToOpenDoor);

	return *this;
}

Room& Room::openRoom(const Direction lockedDoorDirection)
{
	m_lockedRoomDirectionsFlags &= ~getMaskFromDirection(lockedDoorDirection);

	m_itemToOpenDoor.at(static_cast<std::size_t>(lockedDoorDirection)) = nullptr;

	// Unlock the door on the other side if that room is also locked
	if (m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection)) &&
		m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection))->isRoomLocked(getOppositeDirection(lockedDoorDirection)))
			m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection))->openRoom(getOppositeDirection(lockedDoorDirection));

	return *this;
}

bool Room::isRoomLocked(const Direction dir) const
{
	return (m_lockedRoomDirectionsFlags & getMaskFromDirection(dir));
}


Room& Room::linkAdjacentRoom(Room* roomToAdd, const Direction direction)
{
	// Check if respective adjacent links between rooms are empty before linking
	if (!(m_adjacentRooms.at(static_cast<std::size_t>(direction))) &&
		!(roomToAdd->m_adjacentRooms.at(static_cast<std::size_t>(getOppositeDirection(direction)))))
	{
		m_adjacentRooms.at(static_cast<std::size_t>(direction)) = roomToAdd;
		roomToAdd->m_adjacentRooms.at(static_cast<std::size_t>(getOppositeDirection(direction))) = this;
	}
	else
		assert("rooms at these directions already exist");

	return *this;
}

std::ostream& operator<<(std::ostream& out, const Room& room)
{
	out << room.m_basicDescription;

	for (const auto& i : room.m_objects)
		out << '\n' << i->getInRoomDescription();

	if (room.getIsSafeRoom())
		std::cout << "\nЭта комната выглядит безопасной. Вы можете (отдохнуть) здесь.";

	out << "\nВыходы есть на: [";

	for (std::size_t i{ 0 }; i < room.m_adjacentRooms.size(); ++i)
		if (room.m_adjacentRooms.at(i))
		{
			out << getStringFromDirection(static_cast<Direction>(i)) << "е ";
			if (room.isRoomLocked(static_cast<Direction>(i)))
				out << "\b(заперто) ";
		}

	out << "\b]";

	return out;
}