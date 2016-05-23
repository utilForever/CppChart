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
	};
}

#endif