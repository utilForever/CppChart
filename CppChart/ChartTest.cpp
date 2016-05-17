#include <thread>

#include "Chart.h"
#include "Bar.h"

void DrawOnScreen(CppChart::Chart*);
void ChartTest();

int main()
{
	std::thread t(ChartTest);
	t.join();

	return 0;
}

void DrawOnScreen(CppChart::Chart* graph)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Plotting", sf::Style::Default, settings);

	graph->m_chartOffsets.x = 2;
	graph->m_chartOffsets.y = 2;
	graph->SetDimensions(700, 500);
	graph->m_screenMargins.top = 25;
	graph->m_screenMargins.bottom = 25;
	graph->m_screenMargins.left = 25;
	graph->m_screenMargins.right = 25;
	graph->SetDefaultLegendMetrics();

	window.clear(sf::Color(255, 255, 255));
	graph->DrawToScreen(&window);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape ||
					event.key.code == sf::Keyboard::Return)
				{
					window.close();
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void ChartTest()
{
	char option;
	CppChart::Chart* graph;

	do
	{
		std::cout << "Which graph do you want to see ?\n";
		std::cout << "1. Bar Graph\n";
		std::cout << "Enter your option [1-1] : ";
		std::cin >> option;

		switch (option)
		{
		case '1':
			graph = new CppChart::BarChart(std::vector<CppChart::DataElement>
			{ 
				CppChart::DataElement{ "AAA", sf::Color(255, 105, 97), 23 },
				CppChart::DataElement{ "BBB", sf::Color(255, 179, 71), 14 },
				CppChart::DataElement{ "CCC", sf::Color(119, 190, 119), 33 },
				CppChart::DataElement{ "DDD", sf::Color(150, 111, 214), 12 }
			}, false);
			break;

		default:
			return;
		}

		DrawOnScreen(graph);
		std::cin.get();
		std::cin.get();

		delete graph;

		// Clear Screen
		for (int i = 0; i < 1000; ++i)
		{
			std::cout << "\n";
		}
	} while (true);
}