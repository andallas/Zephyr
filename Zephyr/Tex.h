#ifndef TEX_H
#define TEX_H

#include <string>
#include <glew.h>
#include <SOIL.h>

class Tex
{
public:
	Tex();
	virtual ~Tex();

	void Bind(unsigned int unit);
	void Init(const std::string& texturePath, GLint textureFormat);

private:
	Tex(const Tex& other) {}
	void operator=(const Tex& other) {}

	GLuint texture;
};

#endif