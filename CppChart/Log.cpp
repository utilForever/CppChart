#include <sstream>

#include "Log.h"

namespace CppChart
{
	std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v)
	{
		stream << "(" << v.x << ", " << v.y << ")";
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Vector2u& v)
	{
		stream << "(" << v.x << ", " << v.y << ")";
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Color& c)
	{
		stream << "(" << static_cast<int>(c.r) << ", " << static_cast<int>(c.g) << "," << static_cast<int>(c.b) << ")";
		return stream;
	}

	template <typename T>
	std::string ToString(const T& val)
	{
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}
}