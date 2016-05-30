#include <sstream>
#include <iomanip>

#include "Line.h"

namespace CppChart
{
	LineChart::LineChart(const std::vector<DataElement>& d) :
		m_anchorColor(sf::Color(88, 172, 250)), m_guideColor(sf::Color(100, 100, 100)),
		m_lineColor(sf::Color::Black), m_fillColor(sf::Color::Cyan),
		m_anchorSize(8.0f), m_lineThickness(2.0f), m_fill(true),
		m_displayGuides(true), m_displayValues(true), m_data(d),
		m_gap(0.0f), m_startPos(0.0f), m_max(0.0f),
		m_hGuide(true), m_vGuide(true), m_xAxisGuide(true), m_yAxisGuide(true)
	{
		
	}

	void LineChart::Render()
	{
		LogFnStart();

		float x = m_chartOffsets.x / 2.0f, y = m_chartOffsets.y / 2.0f;
		float ratio = (m_chartHeight - m_chartOffsets.y - m_anchorSize - 1.2f * m_axes.labels.fontSize) / m_max;
		float item;

		m_gap = (m_chartWidth - m_chartOffsets.x) / m_data.size();
		
		float width = (m_chartWidth - 2.0f * m_chartOffsets.x - m_gap * static_cast<float>(m_data.size())) / static_cast<float>(m_data.size());

		sf::RectangleShape line;
		sf::Vector2f first, second;
		sf::Text text, values;

		m_fill = true;

		if (!m_legend.m_exists)
		{
			text.setFont(m_axes.labels.font);
			text.setColor(m_axes.labels.fontColor);
			text.setCharacterSize(m_axes.labels.fontSize);
		}

		if (m_displayValues)
		{
			values.setFont(m_axes.labels.font);
			values.setCharacterSize(m_axes.labels.fontSize);
		}

		DrawFillPolygon(ratio, m_gap);

		bool isGuide = true;
		for (auto data : m_data)
		{
			item = data.value * ratio;
			second = sf::Vector2f(x, m_chartHeight - y - item);
			// TODO: Log Function Improvement
			// Log("Line : ", second);
			line = MakeRect(first, second, m_lineThickness);
			line.setFillColor(m_lineColor);
			m_chartTexture.draw(line);
			first = second;

			if (!m_legend.m_exists)
			{
				text.setString(data.name);
				SetTextAtCenter(text, x, m_chartHeight - y - 1.2f * m_axes.labels.fontSize, width + m_gap, m_axes.labels.fontSize);
				text.move(sf::Vector2f(-m_gap / 2.0f, 0.0f));
				m_chartTexture.draw(text);
			}

			if (m_displayValues)
			{
				values.setColor(data.color);
				values.setString([&]()
				{
					std::ostringstream oss;
					oss << std::setprecision(2) << data.value;
					return oss.str();
				}());
				SetTextAtCenter(values, x, m_chartHeight - y - item - m_axes.labels.fontSize / 2.0f, width + m_gap, m_axes.labels.fontSize);
				values.move(sf::Vector2f(-m_gap / 2.0f, -m_anchorSize - m_axes.labels.fontSize));

				if (isGuide)
				{
					values.move(sf::Vector2f(values.getString().getSize() * m_axes.labels.fontSize / 2.0f, 0.0f));
				}

				m_chartTexture.draw(values);
			}

			if (isGuide)
			{
				DrawAxisGuides(first.x, first.y);
				isGuide = false;
			}

			DrawAxisAnchors(first.x, first.y);

			x += m_gap;
		}

		x = m_chartOffsets.x / 2.0f;
		
		for (auto& data : m_data)
		{
			item = data.value * ratio;
			DrawValueAnchor(x, m_chartHeight - y - item, data.color);
			x += m_gap;
		}

		DrawAxes();

		LogFnEnd();
	}

	void LineChart::DrawAxisAnchors(float x, float y)
	{
		LogFnStart();

		if (m_yAxisGuide)
		{
			m_anchor.setPosition(sf::Vector2f(m_chartOffsets.x / 2.0f - m_anchorSize / 2.0f, y - m_anchorSize / 2.0f));
			m_anchor.setRadius(m_anchorSize / 2.0f);
			m_chartTexture.draw(m_anchor);
		}

		if (m_xAxisGuide)
		{
			m_anchor.setPosition(sf::Vector2f(x - m_anchorSize / 2.0f, m_chartHeight - m_chartOffsets.y / 2.0f - m_anchorSize / 2.0f - m_axes.labels.fontSize));
			m_anchor.setRadius(m_anchorSize / 2.0f);
			m_chartTexture.draw(m_anchor);
		}

		LogFnEnd();
	}

	void LineChart::DrawValueAnchor(float x, float y, const sf::Color& fillColor)
	{
		LogFnStart();

		m_anchor.setPosition(sf::Vector2f(x - m_anchorSize, y - m_anchorSize));
		m_anchor.setRadius(m_anchorSize);
		m_anchor.setFillColor(fillColor);
		m_chartTexture.draw(m_anchor);

		LogFnEnd();
	}
	
	void LineChart::DrawAxisGuides(float x, float y)
	{
		LogFnStart();

		if (m_vGuide)
		{
			DrawDottedLine(&m_chartTexture, sf::Vector2f(x, y),
				sf::Vector2f(x, m_chartHeight - m_chartOffsets.y / 2.0f - m_axes.labels.fontSize), m_guideColor);
		}

		if (m_hGuide)
		{
			DrawDottedLine(&m_chartTexture, sf::Vector2f(m_chartOffsets.x / 2.0f, y),
				sf::Vector2f(x, y), m_guideColor);
		}

		LogFnEnd();
	}

	void DrawFillPolygon(float, float);
}
