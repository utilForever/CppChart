#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cmath>

#include "SFML/Graphics.hpp"
#include "Log.h"

namespace CppChart
{
	const float A2R = 3.1415f / 180.0f;

	enum class Position
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	enum class Shape
	{
		RECTANGULAR,
		CIRCULAR
	};

	enum class Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	sf::RectangleShape MakeRect(sf::Vector2f, sf::Vector2f, float = 1.0f);
	void DrawDottedLine(sf::RenderTarget*, const sf::Vector2f&, const sf::Vector2f&, const sf::Color&, float = 3.0f, float = 1.0f);
	void SetTextAtCenter(sf::Text&, float, float, float, float);
	sf::CircleShape PlotPoint(float, float, float, const sf::Color&);
}

#endif