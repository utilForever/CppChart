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


	void GraphLegend::Render()
	{
		LogFnStart();

		float lx = 0.0f, ly = 0.0f;

		m_texture.create(m_width, m_height);
		m_texture.clear(m_bgColor);
		CreateLegendObjects();

		switch (m_orientation)
		{
		case Orientation::VERTICAL:
			for (auto& e : m_legend)
			{
				lx = 0.0f;
				e.m_text.setCharacterSize(m_fontSize);
				e.m_text.setFont(m_font);

				if (m_beforeText)
				{
					e.m_shape->setPosition(sf::Vector2f(lx, ly));
					lx += m_shape.width + 5.0f;
					SetTextAtCenter(e.m_text, lx, ly, m_shape.width, m_shape.height);
				}
				else
				{
					SetTextAtCenter(e.m_text, lx, ly, m_shape.width, m_shape.height);
					lx += m_fontSize * e.m_text.getString().getSize() + 5.0f;
					e.m_shape->setPosition(sf::Vector2f(lx, ly));
				}

				ly += m_shape.height + 5.0f;
				m_texture.draw(e.m_text);
				m_texture.draw(*e.m_shape);
			}
			break;
		case Orientation::HORIZONTAL:
			for (auto& e : m_legend)
			{
				ly = 0.0f;
				e.m_text.setCharacterSize(m_fontSize);
				e.m_text.setFont(m_font);

				if (m_beforeText)
				{
					e.m_shape->setPosition(sf::Vector2f(lx, ly));
					ly += m_shape.height;
					SetTextAtCenter(e.m_text, lx, ly, m_shape.width, m_shape.height);
				}
				else
				{
					SetTextAtCenter(e.m_text, lx, ly, m_shape.width, m_shape.height);
					ly += m_fontSize;
					e.m_shape->setPosition(sf::Vector2f(lx, ly));
				}

				lx += m_shape.width + 5.0f;
				m_texture.draw(e.m_text);
				m_texture.draw(*e.m_shape);
			}
			break;
		default:
			throw std::exception("This is never allowed to happen.");
		}

		LogFnEnd();
	}
}