#ifndef CHART_H
#define CHART_H

#include "Graphics.h"
#include "GraphLegend.h"

namespace CppChart
{
	class Chart
	{
	public:
		float m_chartWidth, m_chartHeight;
		float m_screenWidth, m_screenHeight;

		float m_axesThickness;

		struct
		{
			float x, y;
		} m_chartOffsets;

		struct
		{
			float top, bottom, right, left;
		} m_screenMargins;

		struct
		{
			float thickness;
			sf::Color color;
			struct
			{
				float fontSize;
				sf::Color fontColor, bgColor;
				sf::Font font;
			} labels;
		} m_axes;

		GraphLegend m_legend;

		Chart() :
			m_chartWidth(0.0f), m_chartHeight(0.0f), m_screenWidth(0.0f), m_screenHeight(0.0f), m_axesThickness(0.0f),
			m_chartOffsets{ 0.0f, 0.0f }, m_axes{2.0f, sf::Color::Black, { 15.0f, sf::Color::Black, sf::Color::White, sf::Font() } },
			m_screenBgColor(sf::Color::White), m_chartBgColor(sf::Color::White) { }

		virtual ~Chart()
		{

		}

		void SetChartBackgroundColor(const sf::Color& c)
		{
			m_chartBgColor = c;
		}

		void SetScreenBackgroundColor(const sf::Color& c)
		{
			m_screenBgColor = c;
		}

		void AddTextElement(const sf::Text& t)
		{
			m_textElements.push_back(t);
		}

		void SetDimensions(float x, float y)
		{
			m_screenWidth = x;
			m_screenHeight = y;
		}

		void SetDefaultLegendMetrics(Position p = Position::LEFT)
		{
			m_legend.m_position = p;
		}

		void DrawAxes();
		void DrawTextElements();
		void DrawToScreen(sf::RenderWindow*);

		virtual void Render() = 0;

	protected:
		void CopyToScreen(sf::RenderWindow*);
		void CreateTexture();
		void CreateLegendMetrics();
		void LoadFonts();

		sf::RenderTexture m_chartTexture;
		sf::RenderTexture m_screenTexture;
		sf::RenderTexture m_legendTexture;

		sf::Color m_screenBgColor;
		sf::Color m_chartBgColor;

		std::vector<sf::Text> m_textElements;
	};
}

#endif