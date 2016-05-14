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

	void DrawDottedLine(sf::RenderTarget* window, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color, float gap, float thickness)
	{
		LogFnStart();

		float dist = sqrt((start.x - end.x) * (start.x - end.x) + (start.y - end.y) * (start.y - end.y));
		float covered, ratio;
		float x, y;
		int totalSegments = dist / gap;
		bool draw = true;
		sf::Vector2f first = start, second;
	
		covered = gap;

		for (int i = 0; i < totalSegments; ++i)
		{
			if (draw)
			{
				ratio = covered / dist;
				x = start.x * (1.0f - ratio) + end.x * ratio;
				y = start.y * (1.0f - ratio) + end.y * ratio;
				second = sf::Vector2f(x, y);

				sf::RectangleShape rect = MakeRect(first, second, thickness);
				rect.setFillColor(color);
				window->draw(rect);
			}
			else
			{
				ratio = covered / dist;
				x = start.x * (1.0f - ratio) + end.x * ratio;
				y = start.y * (1.0f - ratio) + end.y * ratio;
				first = sf::Vector2f(x, y);
			}

			draw = !draw;
			covered += gap;
		}

		if ((totalSegments % 2 == 0) && ((dist / gap) > static_cast<float>(totalSegments)))
		{
			sf::RectangleShape rect = MakeRect(first, end, thickness);
			rect.setFillColor(color);
			window->draw(rect);
		}

		LogFnEnd();
	}

	void SetTextAtCenter(sf::Text& text, float x, float y, float w, float h)
	{
		LogFnStart();

		float offsetX = (w - text.getLocalBounds().width) / 2.0f;
		float offsetY = (h - text.getLocalBounds().height) / 2.0f;

		text.setPosition(sf::Vector2f(x + offsetX, y + offsetY));

		LogFnEnd();
	}

	sf::CircleShape PlotPoint(float x, float y, float r, const sf::Color& color)
	{
		LogFnStart();

		sf::CircleShape cs(r);
		cs.setPosition(sf::Vector2f(x, y));
		cs.setFillColor(color);

		LogFnEnd();

		return cs;
	}

	SectorShape::SectorShape(float r, float a, const sf::Vector2f& c) :
		m_radius(r), m_angle(a), m_center(c)
	{
		LogFnStart();

		m_points = 2u + static_cast<unsigned int>(0.05f * m_radius * m_angle);
		m_pie = sf::VertexArray(sf::TrianglesFan, m_points);

		Update();

		LogFnEnd();
	}

	void SectorShape::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		LogFnStart();

		states.transform *= getTransform();
		target.draw(m_pie, states);

		LogFnEnd();
	}

	void SectorShape::Update(float temp)
	{
		LogFnStart();

		float incr = m_angle / static_cast<float>(m_points - 2u);
		float x, y;

		m_pie[0].position = m_center;
		m_pie[0].color = m_fillColor;

		for (size_t i = 1; i < m_points; ++i)
		{
			x = m_radius * cos(A2R * temp);
			y = m_radius * sin(A2R * temp);
			
			m_pie[i].position = sf::Vector2f(x, y) + m_center;
			m_pie[i].color = m_fillColor;

			temp += incr;
		}

		LogFnEnd();
	}
}