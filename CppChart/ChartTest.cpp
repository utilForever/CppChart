#include <thread>

void ChartTest();

int main()
{
	std::thread t(ChartTest);
	t.join();

	return 0;
}

void ChartTest()
{

}