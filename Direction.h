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
		std::make_pair("�����", Direction::north),
		std::make_pair("������", Direction::north),
		std::make_pair("�", Direction::north),
		std::make_pair("������", Direction::east),
		std::make_pair("�������", Direction::east),
		std::make_pair("�", Direction::east),
		std::make_pair("��", Direction::south),
		std::make_pair("���", Direction::south),
		std::make_pair("�", Direction::south),
		std::make_pair("�����", Direction::west),
		std::make_pair("������", Direction::west),
		std::make_pair("�", Direction::west),
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