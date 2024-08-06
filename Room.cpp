#include <cassert>
#include <iostream>

#include "Direction.h"
#include "Room.h"
#include "Player.h"

Room& Room::insertObject(Object object)
{
	m_objects.push_back(std::move(object));

	return *this;
}

Room& Room::insertItem(Item* item)
{
	m_item = item;
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

	// Unlock the door on the other side if the room is also locked
	if (m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection)) &&
		m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection))->isRoomLocked(getOppositeDirection(lockedDoorDirection)))
			m_adjacentRooms.at(static_cast<std::size_t>(lockedDoorDirection))->openRoom(getOppositeDirection(lockedDoorDirection));

	return *this;
}

bool Room::isRoomLocked(const Direction dir)
{
	return (m_lockedRoomDirectionsFlags & getMaskFromDirection(dir));
}


Room& Room::linkAdjacentRoom(Room* roomToAdd, const Direction direction)
{
	// Check if respective adjacent links between rooms are empty before linking
	if ((m_adjacentRooms.at(static_cast<std::size_t>(direction)) == nullptr) &&
		(roomToAdd->m_adjacentRooms.at(static_cast<std::size_t>(getOppositeDirection(direction))) == nullptr))
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
	if (room.m_item)
		out << '\n' << room.m_item->getInRoomDescription();

	return out;
}