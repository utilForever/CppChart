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

		m_axes.labels.font.loadFromFile("NotoSans.ttf");
		m_legend.m_font.loadFromFile("NotoSans.ttf");

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
}