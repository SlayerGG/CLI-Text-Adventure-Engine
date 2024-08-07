#ifndef LEVER_H
#define LEVER_H
#include "Object.h"
#include "Room.h"

class Lever : public Object
{
private:
	std::string m_activationText;
	std::string m_alreadyActivatedText;
	Room* m_roomToOpen{};
	Direction m_openRoomDirection{};
	bool m_canActivate{ true };
	bool m_isActivated{ false };

public:
	Lever(std::string_view name, std::string_view inRoomDescription,
		std::string_view inspectionDescription, std::vector<std::string> keywords,
		std::string_view activationText, std::string_view alreadyActivatedText,
		Room* roomToOpen, Direction openRoomDirection) :
		Object{ name, inRoomDescription, inspectionDescription, keywords },
		m_activationText{ activationText }, m_alreadyActivatedText{alreadyActivatedText}, 
		m_roomToOpen{roomToOpen}, m_openRoomDirection{openRoomDirection}
	{
	}

	void activate() override;

	bool canActivate() const override { return m_canActivate; }
};
#endif