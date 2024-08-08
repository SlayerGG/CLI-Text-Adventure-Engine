#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

enum class Direction
{
	north,
	east,
	south,
	west,
	totalDirections
};


namespace DirectionMap
{
	inline const std::unordered_map<std::string, Direction> directionMap
	{
		std::make_pair("север", Direction::north),
		std::make_pair("севере", Direction::north),
		std::make_pair("с", Direction::north),
		std::make_pair("восток", Direction::east),
		std::make_pair("востоке", Direction::east),
		std::make_pair("в", Direction::east),
		std::make_pair("юг", Direction::south),
		std::make_pair("юге", Direction::south),
		std::make_pair("ю", Direction::south),
		std::make_pair("запад", Direction::west),
		std::make_pair("западе", Direction::west),
		std::make_pair("з", Direction::west),
	};

	constexpr std::uint8_t north{ 0b0001 };
	constexpr std::uint8_t east{ 0b0010 };
	constexpr std::uint8_t south{ 0b0100 };
	constexpr std::uint8_t west{ 0b1000 };
}

Direction getOppositeDirection(const Direction dir);
std::uint8_t getMaskFromDirection(const Direction dir);
std::string_view getStringFromDirection(const Direction direction);
#endif