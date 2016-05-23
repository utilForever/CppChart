#ifndef LINE_H
#define LINE_H

#include "Chart.h"

namespace CppChart
{
	class LineChart : public Chart
	{
	public:
		LineChart() = default;
		LineChart(const std::vector<DataElement>&);

		void Render() override;

		sf::Color m_anchorColor, m_guideColor, m_lineColor, m_fillColor;
		float m_anchorSize, m_lineThickness;

		bool m_displayGuides;
		bool m_displayValues;
		bool m_fill;

	protected:
		void DrawAxisAnchors(float, float);
		void DrawValueAnchor(float, float, const sf::Color&);
		void DrawAxisGuides(float, float);
		void DrawFillPolygon(float, float);

		sf::CircleShape m_anchor;

		std::vector<DataElement> m_data;

		float m_gap, m_startPos;
		float m_max;

		bool m_hGuide, m_vGuide;
		bool m_xAxisGuide, m_yAxisGuide;
	};
}

#endif