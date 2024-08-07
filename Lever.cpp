#include <iostream>

#include "Lever.h"

void Lever::activate()
{
	if (m_isActivated)
	{
		std::cout << m_alreadyActivatedText << '\n';

		return;
	}

	m_roomToOpen->openRoom(m_openRoomDirection);

	m_isActivated = true;

	std::cout << m_activationText << '\n';
}