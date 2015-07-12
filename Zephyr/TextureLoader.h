#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include <glew.h>
#include <SOIL.h>

class TextureLoader
{
public:
	static GLuint LoadTexture(std::string texturePath);
};

#endif