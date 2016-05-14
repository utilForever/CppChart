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
}