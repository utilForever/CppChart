#include "ChartUtil.h"

namespace CppChart
{
	unsigned int CountDigit(float val)
	{
		unsigned int digit = 0u;
		
		int v = static_cast<int>(val);
		while (v > 0)
		{
			digit++;
			v /= 10;
		}

		return digit;
	}
}