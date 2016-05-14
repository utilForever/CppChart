#ifndef GRAPHICS_H
#define GRAPHICS_H

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
		CIRCULAR,
		UNKNOWN
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

	class SectorShape : public sf::Transformable, public sf::Drawable
	{
	public:
		SectorShape() :
			m_radius(0.0f), m_angle(0.0f), m_points(0)
		{
			
		}

		SectorShape(float, float, const sf::Vector2f& = sf::Vector2f(0.0f, 0.0f));

		void SetCenter(const sf::Vector2f& c)
		{
			m_center = c;
			Update();
		}

		void SetFillColor(const sf::Color& c)
		{
			m_fillColor = c;
			Update();
		}

		void Rotate(float a)
		{
			LogFnStart();
			Update(a);
			LogFnEnd();
		}

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void Update(float = 0.0f);

		float m_radius;
		float m_angle;
		sf::Vector2f m_center;
		sf::VertexArray m_pie;
		sf::Color m_fillColor;
		unsigned int m_points;
	};

	class TriangleShape : public sf::Shape
	{
	public:
		TriangleShape(const sf::Vector2f v1, const sf::Vector2f v2, const sf::Vector2f v3) :
			m_vertex{ v1, v2, v3 } { }

		virtual unsigned int GetPointCount() const
		{
			return 3u;
		}

		virtual sf::Vector2f GetPoint(unsigned int index) const
		{
			return m_vertex[index];
		}

	private:
		sf::Vector2f m_vertex[3];
	};
}

#endif