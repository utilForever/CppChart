#include "Bar.h"

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
}