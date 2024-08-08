#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <string_view>

#include "Direction.h"

Direction getOppositeDirection(const Direction dir)
{
	switch (dir)
	{
	case Direction::north:	return Direction::south;
	case Direction::east:	return Direction::west;
	case Direction::south:	return Direction::north;
	case Direction::west:	return Direction::east;
	default:				throw std::runtime_error{"Unknown direction passed to getOppositeDirection"};
	}
}

std::uint8_t getMaskFromDirection(const Direction dir)
{
	switch (dir)
	{
	case Direction::north:	return DirectionMap::north;
	case Direction::east:	return DirectionMap::east;
	case Direction::south:	return DirectionMap::south;
	case Direction::west:	return DirectionMap::west;
	default:				throw std::runtime_error{ "Unknown direction passed to getDirectionMaskFromDirection" };
	}
}

std::string_view getStringFromDirection(const Direction direction)
{
	switch (direction)
	{
	using enum Direction;
	case (north):	{ return "север"; }
	case (east):	{ return "восток"; }
	case (south):	{ return "юг"; }
	case (west):	{ return "запад"; }
	default:		assert("unknown locked door direction found");
	}

	return "error";
}