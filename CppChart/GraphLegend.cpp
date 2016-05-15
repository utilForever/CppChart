#include "GraphLegend.h"

namespace CppChart
{
	GraphLegendUnit::GraphLegendUnit(float x, float y, const sf::Color& c, const std::string& str)
	{
		LogFnStart();

		SetRectangleShape(x, y, c);
		SetString(str);

		LogFnEnd();
	}

	GraphLegendUnit::GraphLegendUnit(float r, const sf::Color& c, const std::string& str)
	{
		LogFnStart();

		SetCircleShape(r, c);
		SetString(str);

		LogFnEnd();
	}
}