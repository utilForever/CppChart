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

	struct DataElement : public DataFormat
	{
		DataElement(const std::string& _name, const sf::Color& _color, float _value) :
			DataFormat(_name, _color), value(_value) { }

		bool operator<(const DataElement& e) const
		{
			return value < e.value;
		}

		float value;
	};

	struct RangedDataElement : public DataFormat
	{
		RangedDataElement(const std::string _name, const sf::Color& _color, float _x, float _y, float _value) :
			DataFormat(_name, _color), x(_x), y(_y), value(_value) { }

		bool operator<(const RangedDataElement& e) const
		{
			return value < e.value;
		}

		float x, y;
		float value;
	};

	struct Triplet : public DataFormat
	{
		Triplet(const std::string _name, const sf::Color& _color, float _x, float _y, float _value) :
			DataFormat(_name, _color), x(_x), y(_y), value(_value) { }

		bool operator<(const Triplet& e) const
		{
			return value < e.value;
		}

		float x, y;
		float value;
	};
}

#endif