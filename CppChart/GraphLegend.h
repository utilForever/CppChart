#ifndef GRAPH_LEGEND_H
#define GRAPH_LEGEND_H

#include "Graphics.h"

namespace CppChart
{
	class GraphLegendUnit
	{
	public:
		GraphLegendUnit() : m_shape(nullptr), m_shapeType(Shape::UNKNOWN) { }
		GraphLegendUnit(float, float, const sf::Color&, const std::string&);
		GraphLegendUnit(float, const sf::Color&, const std::string&);

		void SetRectangleShape(float, float, const sf::Color&);
		void SetCircleShape(float, const sf::Color&);
		
		void SetOutlineThickness(float t) const
		{
			m_shape->setOutlineThickness(t);
		}

		void SetOutlineColor(const sf::Color& c) const
		{
			m_shape->setOutlineColor(c);
		}

		void SetString(const std::string& str)
		{
			m_text.setString(str);
		}

		void SetTextColor(const sf::Color& c)
		{
			m_text.setColor(c);
		}

		std::string GetString() const
		{
			return m_text.getString();
		}

		friend class GraphLegend;
		friend class Chart;

	protected:
		sf::Shape* m_shape;
		sf::Text m_text;
		Shape m_shapeType;
	};
}

#endif