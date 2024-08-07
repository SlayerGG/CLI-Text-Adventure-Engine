#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <unordered_map>
#include <utility>

#include "Object.h"
#include "Direction.h"
#include "Room.h"

class Player
{
public:
	enum Action
	{
		north,
		east,
		south,
		west,
		look,
		get,
		inventory,
		open,
		inspect,
		use,
		totalActions,
		unknownAction
	};

	enum ObjectToOpen
	{
		door,
		totalObjects,
		unknownObject
	};

private:
	Room* m_currentRoom;

	std::map<std::string_view, Object*> m_inventory;

	static inline const std::unordered_map<std::string_view, Action> m_actions
	{
		std::make_pair("север", Action::north),
		std::make_pair("с", Action::north),
		std::make_pair("c", Action::north),
		std::make_pair("восток", Action::east),
		std::make_pair("в", Action::east),
		std::make_pair("юг", Action::south),
		std::make_pair("ю", Action::south),
		std::make_pair("запад", Action::west),
		std::make_pair("з", Action::west),
		std::make_pair("осмотреться", Action::look),
		std::make_pair("взять", Action::get),
		std::make_pair("инвентарь", Action::inventory),
		std::make_pair("открыть", Action::open),
		std::make_pair("рассмотреть", Action::inspect),
		std::make_pair("использовать", Action::use)
	};

	static inline const std::unordered_map<std::string_view, ObjectToOpen> m_objectsToOpen
	{
		std::make_pair("дверь", ObjectToOpen::door),
		std::make_pair("двери", ObjectToOpen::door),
	};

	void describeItemFromInventory(const std::vector<Object*>& itemList) const;

	// Checks if the door can be opened from player standpoint.
	// room is the Room to be opened, dir is the Direction from the room view
	void checkAndOpenDoor (Room* room, const Direction dir) const;
	// Checks what doors are around the player currently.
	// Calls checkAndOpenDoor to actually open the door
	void openDoorLogic() const;

public:
	Player(Room* startingRoom) : m_currentRoom{ startingRoom }
	{
	}

	bool move( const Direction dir );

	void describeRoom() const;

	void printInventory() const;

	void getItem(std::string_view itemName);
	bool ifItemInInventory(Item* itemToCheck) const;

	void openSomething(std::string_view objectToOpen) const;

	void inspectSomething(std::string_view objectToInspect) const;

	void useSomething(std::string_view objectToUse) const;

	static const std::unordered_map<std::string_view, Action>& getActions() { return m_actions; }

	static const std::unordered_map<std::string_view, ObjectToOpen>& getObjectsToOpen() { return m_objectsToOpen; }
};
#endif // ! PLAYER_H