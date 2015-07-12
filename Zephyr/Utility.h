#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <iostream>

class Utility
{
public:
	static std::string BaseDirectory();
	static std::string ShaderDirectory();
	static std::string ImageDirectory();
};

#endif