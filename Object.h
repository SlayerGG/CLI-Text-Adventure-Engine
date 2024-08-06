#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

class Object
{
private:
	std::string m_name;
	std::string m_inRoomDescription;
	std::string m_inspectionDescription;
	std::vector<std::string> m_keywords{};

public:
	Object(std::string_view name, std::string_view inRoomDescription,
		std::string_view inspectionDescription, std::vector<std::string> keywords) :
		m_name{ name }, m_inRoomDescription{ inRoomDescription },
		m_inspectionDescription{ inspectionDescription }, m_keywords{ std::move(keywords) }
	{
	}

	std::string_view getName() const { return m_name; }
	std::string_view getInRoomDescription() const { return m_inRoomDescription; }
	std::string_view getInspectionDescription() const { return m_inspectionDescription; }
	const std::vector<std::string>& getKeywords() const { return m_keywords; }

	virtual ~Object()
	{
	}
};
#endif