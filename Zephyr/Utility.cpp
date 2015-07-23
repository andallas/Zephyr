#include "Utility.h"


std::string Utility::BaseDirectory()
{
	char full[_MAX_PATH];
	if (_fullpath(full, ".\\", _MAX_PATH) != NULL)
	{
		return full;
	}

	std::cerr << "ERROR::MAIN::BASE_DIRECTORY::INVALID_PATH\n" << std::endl;

	return "";
}

std::string Utility::ShaderDirectory()
{
	return (BaseDirectory() + "Resources\\Shaders\\");
}

std::string Utility::ImageDirectory()
{
	return (BaseDirectory() + "Resources\\Images\\");
}

std::string Utility::ModelDirectory()
{
	return (BaseDirectory() + "Resources\\Models\\");
}
