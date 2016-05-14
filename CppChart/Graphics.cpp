#include "Graphics.h"

namespace CppChart
{
	sf::RectangleShape MakeRect(sf::Vector2f first, sf::Vector2f second, float thickness)
	{
		sf::RectangleShape plot;
		float dist = sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));

		plot.setSize(sf::Vector2f(dist, thickness));

		if (first.y > second.y)
		{
			std::swap(first, second);
		}

		plot.setPosition(first);
		plot.setOrigin(0.0f, plot.getSize().y / 2.0f);

		float m = (second.y - first.y) / (second.x - first.x);
		float angle = (180.0f / 3.1415f) * atan(m >= 0.0f ? m : -m);

		if ((first.x - second.x) > 0.01f)
		{
			angle = 180.0f - angle;
		}

		plot.rotate(angle);

		return plot;
	}
}