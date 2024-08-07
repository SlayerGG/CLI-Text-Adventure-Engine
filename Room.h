#ifndef ROOM_H
#define ROOM_H
#include <cstdint>
#include <string_view>
#include <array>
#include <vector>
#include <utility>

#include "Direction.h"
#include "Item.h"

class Room
{
private:
	std::array<Room*, static_cast<int>(Direction::totalDirections)> m_adjacentRooms{};
	std::string_view m_basicDescription;
	std::uint8_t m_lockedRoomDirectionsFlags{0b0000}; // using bit manipulation
	std::array<Item*, static_cast<int>(Direction::totalDirections)> m_itemToOpenDoor{};
	std::vector<Object> m_simpleObjects;
	// TODO: apply polymorphism here with a map so that it's possible to store
	// objects of any derived type
	Item* m_item{};

public:
	Room(std::string_view description) :  m_basicDescription{ description }
	{
	}

	// Uses adjacency list data structure to link rooms
	Room& linkAdjacentRoom(Room* room, const Direction direction);
	const std::array<Room*, static_cast<int>(Direction::totalDirections)>& getAdjacentRooms() const { return m_adjacentRooms; }

	// TODO: Add objects and interactions functionality
	
	// Locks the room in one directional only
	Room& lockRoomUni(const Direction lockedRoomDirection, Item* itemToOpenDoor = nullptr);
	// Locks the room in both directions
	Room& lockRoomBi(const Direction lockedRoomDirection, Item* itemToOpenDoor = nullptr);
	Room& openRoom(const Direction lockedRoomDirection);
	bool isRoomLocked(const Direction dir);
	Item* getItemToOpenDoorPtr(const Direction lockedDoorDirection) const {
		return m_itemToOpenDoor.at(static_cast<std::size_t>(lockedDoorDirection));
	}

	Room& insertSimpleObject(Object object);
	// TODO: implement deleteObject and getObjectPtr
	Room& deleteObject(const Object& object);
	const std::vector<Object>& getSimpleObjects() const{ return m_simpleObjects; }

	Room& insertItem(Item* item);
	void deleteItem() { m_item = nullptr; }
	Item* getItemPtr() const { return m_item; }

	// Prints the description of the room
	friend std::ostream& operator<<(std::ostream& out, const Room& room);
};
#endif