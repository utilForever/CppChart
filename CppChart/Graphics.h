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
}

#endif