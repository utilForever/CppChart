#include "Chart.h"

namespace CppChart
{
	void Chart::DrawAxes()
	{
		LogFnStart();

		sf::RectangleShape xAxis, yAxis;
		xAxis.setFillColor(m_axes.color);
		yAxis.setFillColor(m_axes.color);

		// Y-axis
		yAxis.setPosition(sf::Vector2f(m_chartOffsets.x / 2.0f, m_chartOffsets.y / 2.0f - m_axes.labels.fontSize));
		yAxis.setSize(sf::Vector2f(m_axes.thickness, m_chartHeight - m_chartOffsets.y));
		m_chartTexture.draw(yAxis);

		// X-axis
		xAxis.setPosition(sf::Vector2f(m_chartOffsets.x / 2.0f, m_chartHeight - m_chartOffsets.y / 2.0f - m_axes.thickness - m_axes.labels.fontSize));
		xAxis.setSize(sf::Vector2f(m_chartWidth - m_chartOffsets.x, m_axes.thickness));
		m_chartTexture.draw(xAxis);

		LogFnEnd();
	}

	void Chart::DrawTextElements()
	{
		LogFnStart();

		for (auto& e : m_textElements)
		{
			m_screenTexture.draw(e);
		}

		LogFnEnd();
	}

	void Chart::DrawToScreen(sf::RenderWindow* window)
	{
		LogFnStart();

		CreateTexture();
		LoadFonts();
		Render();
		DrawTextElements();
		CopyToScreen(window);

		LogFnEnd();
	}

	void Chart::CopyToScreen(sf::RenderWindow* window)
	{
		LogFnStart();

		// Background Screen Texture
		sf::Sprite bSprite;
		m_screenTexture.setSmooth(true);
		m_screenTexture.display();
		bSprite.setTexture(m_screenTexture.getTexture());
		window->draw(bSprite);

		// Foreground Chart Texture (Adjust for margins)
		sf::Sprite cSprite;
		m_chartTexture.display();
		m_chartTexture.setSmooth(true);
		cSprite.setTexture(m_chartTexture.getTexture());
		cSprite.move(sf::Vector2f(m_screenMargins.left, m_screenMargins.top));
		window->draw(cSprite);

		// Legend Drawing
		if (m_legend.m_exists)
		{
			sf::Sprite lSprite;
			m_legend.Render();
			lSprite.setTexture(m_legend.m_texture.getTexture());
			lSprite.move(sf::Vector2f(m_legend.m_x, m_legend.m_y));
			window->draw(lSprite);
		}

		LogFnEnd();
	}

	void Chart::CreateTexture()
	{
		LogFnStart();

		if (m_legend.m_exists)
		{
			CreateLegendMetrics();
		}

		m_chartWidth = m_screenWidth - m_screenMargins.left - m_screenMargins.right;
		m_chartHeight = m_screenHeight - m_screenMargins.top - m_screenMargins.bottom;

		m_chartTexture.create(m_chartWidth, m_chartHeight);
		m_chartTexture.clear(m_chartBgColor);

		m_screenTexture.create(m_screenWidth, m_screenHeight);
		m_screenTexture.clear(m_screenBgColor);

		LogFnEnd();
	}
	
	void Chart::CreateLegendMetrics()
	{
		LogFnStart();

		m_legend.m_x = m_legend.m_y = 0.0f;

		switch (m_legend.m_position)
		{
		case Position::LEFT:
			m_legend.m_orientation = Orientation::VERTICAL;
			m_legend.m_width = 0.2f * m_screenWidth;
			m_legend.m_height = 0.75f * m_screenHeight;
			m_legend.m_x = 0.0f;
			m_legend.m_y = 0.125f * m_screenHeight;
			m_screenMargins.left += m_legend.m_width;
			break;
		case Position::RIGHT:
			m_legend.m_orientation = Orientation::VERTICAL;
			m_legend.m_width = 0.2f * m_screenWidth;
			m_legend.m_height = 0.75f * m_screenHeight;
			m_legend.m_x = 0.8f * m_screenWidth;
			m_legend.m_y = 0.125f * m_screenHeight;
			m_screenMargins.right += m_legend.m_width;
			break;
		case Position::TOP:
			m_legend.m_orientation = Orientation::HORIZONTAL;
			m_legend.m_width = 0.75f * m_screenWidth;
			m_legend.m_height = 0.2f * m_screenHeight;
			m_legend.m_x = 0.125f * m_screenWidth;
			m_screenMargins.top += m_legend.m_height;
			break;
		case Position::BOTTOM:
			m_legend.m_orientation = Orientation::HORIZONTAL;
			m_legend.m_width = 0.5f * m_screenWidth;
			m_legend.m_height = 0.2f * m_screenHeight;
			m_legend.m_x = 0.25f * m_screenWidth;
			m_legend.m_y = 0.8f * m_screenHeight;
			m_screenMargins.bottom += m_legend.m_height;
			break;
		default:
			throw std::exception("This is never allowed to happen.");
		}

		m_legend.m_keyShape = Shape::RECTANGULAR;

		LogFnEnd();
	}

	void Chart::LoadFonts()
	{
		LogFnStart();

		m_axes.labels.font.loadFromFile("NotoSans.ttf");
		m_legend.m_font.loadFromFile("NotoSans.ttf");

		LogFnEnd();
	}
}