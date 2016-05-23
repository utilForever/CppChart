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
}