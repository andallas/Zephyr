#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class Shader
{
public:
	GLuint program;
	std::string vertexPath;
	std::string fragmentPath;
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	void Use();

private:
	std::string ParseShaderFile(const GLchar* sourcePath);
	GLuint Shader::Compile(std::string& shaderCode, std::string type);
	void CompileCheck(GLuint shader, std::string type);
	void LinkCheck();
};

#endif