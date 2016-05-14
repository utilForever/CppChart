#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

inline void Log(std::string str)
{
	std::cout << "[" << __LINE__ << "] " << __FUNCTION__ << " : " << str << std::endl;
}

inline void LogFnStart()
{
	Log("Entered");
}

inline void LogFnEnd()
{
	Log("Finished");
}

inline void NestedLog(std::string str)
{
	std::cout << "\n\t" << str << "\n" << std::endl;
}

namespace CppChart
{
	std::ostream& operator<<(std::ostream&, const sf::Vector2f&);
	std::ostream& operator<<(std::ostream&, const sf::Vector2u&);
	std::ostream& operator<<(std::ostream&, const sf::Color&);

	template <typename T>
	std::string ToString(const T&);
}

#endif