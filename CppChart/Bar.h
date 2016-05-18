#ifndef BAR_H
#define BAR_H

#include "Chart.h"

namespace CppChart
{
	class BarChart : public Chart
	{
	public:
		BarChart(const std::vector<DataElement>&, bool = true, bool = true);

		void Render() override;

		float m_gap;
		unsigned int m_guides;
		bool m_displayGuides;
		bool m_displayValues;

	protected:
		std::vector<DataElement> m_data;
		sf::RectangleShape m_bar;

		float m_max;
		float m_width;
		float m_vSize;
	};

	class MultiBarChart : public Chart
	{
	public:
		MultiBarChart(const std::vector<std::vector<float>>&, const std::vector<std::string>&, const std::vector<sf::Color>&);

		void Render() override;

		float m_gap;
		unsigned int m_guides;
		bool m_displayGuides;
		bool m_displayValues;

	protected:
		std::vector<std::vector<float>> m_multiData;
		std::vector<std::string> m_axesLabels;
		std::vector<sf::Color> m_barColors;

		float m_max;
		float m_width;
		float m_vSize;
	};
}

#endif