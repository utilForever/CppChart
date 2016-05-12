#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#include "SFML/Graphics.hpp"

namespace CppChart
{
	struct DataFormat
	{
		DataFormat(const std::string& _name, const sf::Color& _color) :
			name(_name), color(_color) { }

		std::string name;
		sf::Color color;
	};
}

#endif