#ifndef GRAPH_LEGEND_H
#define GRAPH_LEGEND_H

#include "Graphics.h"
#include "DataFormat.h"

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

	class GraphLegend
	{
	public:
		GraphLegend() :
			orientation(Orientation::UNKNOWN), beforeText(true), textMatchesKeyColor(true), exists(true),
			width(0), height(0), x(0), y(0), position(Position::UNKNOWN),
			keyShape(Shape::UNKNOWN), bgColor(sf::Color::White), fontColor(sf::Color::Black), m_fontSize(0) { }

		void AddData(const std::vector<DataFormat>& d)
		{
			m_legendData = d;
		}

		void Render();

		Orientation orientation;
		bool beforeText;
		bool textMatchesKeyColor;
		bool exists;

		float width, height;
		float x, y;
		Position position;
		Shape keyShape;
		sf::Font font;
		sf::Color bgColor, fontColor;

		union
		{
			struct
			{
				float width;
				float height;
			};

			float radius;
		} shape;

		friend class Chart;

	protected:
		unsigned int GetLongestName() const;
		void CreateLegendObjects();

		std::vector<GraphLegendUnit> m_legend;
		std::vector<DataFormat> m_legendData;
		sf::RenderTexture m_texture;
		float m_fontSize;
	};
}

#endif