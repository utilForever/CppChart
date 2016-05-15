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

	void GraphLegendUnit::SetRectangleShape(float x, float y, const sf::Color& c)
	{
		LogFnStart();

		m_shape = new sf::RectangleShape(sf::Vector2f(x, y));
		m_shape->setFillColor(c);
		m_shapeType = Shape::RECTANGULAR;

		LogFnEnd();
	}

	void GraphLegendUnit::SetCircleShape(float r, const sf::Color& c)
	{
		LogFnStart();

		m_shape = new sf::CircleShape(r);
		m_shape->setFillColor(c);
		m_shapeType = Shape::CIRCULAR;

		LogFnEnd();
	}
}