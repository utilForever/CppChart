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
			m_orientation(Orientation::UNKNOWN), m_beforeText(true), m_textMatchesKeyColor(true), m_exists(false),
			m_width(0), m_height(0), m_x(0), m_y(0), m_position(Position::UNKNOWN),
			m_keyShape(Shape::UNKNOWN), m_bgColor(sf::Color::White), m_fontColor(sf::Color::Black), m_fontSize(0) { }

		void AddData(const std::vector<DataFormat>& d)
		{
			m_legendData = d;
		}

		void Render();

		Orientation m_orientation;
		bool m_beforeText;
		bool m_textMatchesKeyColor;
		bool m_exists;

		float m_width, m_height;
		float m_x, m_y;
		Position m_position;
		Shape m_keyShape;
		sf::Font m_font;
		sf::Color m_bgColor, m_fontColor;

		union
		{
			struct
			{
				float width;
				float height;
			};

			float radius;
		} m_shape;

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