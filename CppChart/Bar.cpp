#include <sstream>
#include <iomanip>

#include "Bar.h"
#include "ChartUtil.h"
#include <cassert>

namespace CppChart
{
	BarChart::BarChart(const std::vector<DataElement>& d, bool al, bool dv) :
		m_gap(10), m_guides(true), m_displayGuides(false), m_displayValues(dv),
		m_data(d), m_width(0), m_vSize(0.0f)
	{
		LogFnStart();

		m_max = (*max_element(m_data.begin(), m_data.end())).value;
		m_legend.m_exists = al;

		if (m_legend.m_exists)
		{
			std::vector<DataFormat> temp;
			for (auto& element : d)
			{
				temp.push_back({ element.name, element.color });
			}
			m_legend.AddData(temp);
		}

		LogFnEnd();
	}

	void BarChart::Render()
	{
		LogFnStart();

		float x = m_chartOffsets.x / 2.0f + m_gap, y = m_chartOffsets.y / 2.0f;
		float ratio = (m_chartHeight - 2.0f * m_chartOffsets.y - m_vSize) / m_max;
		float item;

		sf::Text text, values;
		sf::RectangleShape guideLines;

		m_width = (m_chartWidth - 2.0f * m_chartOffsets.x - m_gap * static_cast<float>(m_data.size())) / static_cast<float>(m_data.size());
		m_vSize = m_width / static_cast<float>(CountDigit(m_max) + 3u);

		if (!m_legend.m_exists)
		{
			text.setFont(m_axes.labels.font);
			text.setColor(m_axes.labels.fontColor);
			text.setCharacterSize(m_axes.labels.fontSize);
		}

		if (m_displayValues)
		{
			values.setFont(m_axes.labels.font);
			values.setCharacterSize(m_vSize);
		}

		if (m_guides)
		{
			// TODO: Fix code
		}

		for (auto& d : m_data)
		{
			item = d.value;
			item *= ratio;

			m_bar.setPosition(x, m_chartHeight - y - item + m_vSize);
			m_bar.setSize(sf::Vector2f(m_width, item - m_axes.labels.fontSize - m_vSize));
			m_bar.setFillColor(d.color);

			m_chartTexture.draw(m_bar);

			if (!m_legend.m_exists)
			{
				text.setString(d.name);
				SetTextAtCenter(text, x, m_chartHeight - y - 1.2f * m_axes.labels.fontSize, m_width + m_gap, m_axes.labels.fontSize);
				text.move(sf::Vector2f(-m_gap / 2.0f, 0.0f));
				m_chartTexture.draw(text);
			}

			if (m_displayValues)
			{
				values.setColor(d.color);
				values.setString([&]()
				{
					std::ostringstream oss;
					oss << std::setprecision(2) << d.value;
					return oss.str();
				}());
				SetTextAtCenter(values, x, m_chartHeight - y - item - m_vSize / 2.0f, m_width + m_gap, m_vSize);
				values.move(sf::Vector2f(-m_gap / 2.0f, 0.0f));
				m_chartTexture.draw(values);
			}

			x += m_width + m_gap;
		}

		DrawAxes();

		LogFnEnd();
	}

	MultiBarChart::MultiBarChart(const std::vector<std::vector<float>>& md, const std::vector<std::string>& al, const std::vector<sf::Color>& bc)
		: m_gap(0.0f), m_guides(0), m_displayGuides(false), m_displayValues(true), m_multiData(md), m_axesLabels(al), m_barColors(bc), m_width(0.0f), m_vSize(0.0f)
	{
		LogFnStart();

		assert(md.size() == al.size());
		assert(md[0].size() == bc.size());

		float temp;
		m_max = *(max_element(md[0].begin(), md[0].end()));

		for (int i = 1; i < al.size(); ++i)
		{
			temp = (*max_element(md[i].begin(), md[i].end()));
			if (temp > m_max)
			{
				m_max = temp;
			}
		}

		LogFnEnd();
	}

	void MultiBarChart::Render()
	{
		LogFnStart();

		float x = m_chartOffsets.x / 2.0f, y = m_chartOffsets.y / 2.0f;
		float ratio = (m_chartHeight - 2.0f * m_chartOffsets.y) / m_max;
		float item;

		sf::RectangleShape bar;
		sf::Text text, values;

		m_width = (m_chartWidth - 2.0f * m_chartOffsets.x) / static_cast<float>((m_multiData[0].size() + 1u) * m_multiData.size());
		m_gap = m_width;
		m_vSize = m_width / static_cast<float>(CountDigit(m_max));

		if (m_displayValues)
		{
			values.setFont(m_axes.labels.font);
			values.setCharacterSize(m_vSize);
		}

		text.setFont(m_axes.labels.font);
		text.setColor(m_axes.labels.fontColor);
		text.setCharacterSize(m_axes.labels.fontSize);

		for (int i = 0; i < m_multiData.size(); ++i)
		{
			x += m_gap;
			text.setString(m_axesLabels[i]);
			SetTextAtCenter(text, x, m_chartHeight - y - 1.2f * m_axes.labels.fontSize, m_width + m_gap, m_axes.labels.fontSize);
			m_chartTexture.draw(text);

			for (int j = 0; j < m_multiData[i].size(); ++j)
			{
				item = m_multiData[i][j] * ratio;
				bar.setPosition(x, m_chartHeight - y - item + m_vSize);
				bar.setSize(sf::Vector2f(m_width, item - m_axes.labels.fontSize - m_vSize));
				bar.setFillColor(m_barColors[j]);
				m_chartTexture.draw(bar);

				if (m_displayValues)
				{
					values.setString([&]()
					{
						std::ostringstream oss;
						oss << std::setprecision(2) << m_multiData[i][j];
						return oss.str();
					}());
					values.setColor(m_barColors[j]);
					SetTextAtCenter(values, x, m_chartHeight - y - item - m_vSize / 2.0f, m_width, m_vSize);
					m_chartTexture.draw(values);
				}

				x += m_width;
			}
		}

		DrawAxes();

		LogFnEnd();
	}
}
