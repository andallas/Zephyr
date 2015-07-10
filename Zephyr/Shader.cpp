#include "Shader.h"

// public
Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	vertexPath = vertexSourcePath;
	fragmentPath = fragmentSourcePath;

	std::string vShaderCode = ParseShaderFile(vertexSourcePath);
	std::string fShaderCode = ParseShaderFile(fragmentSourcePath);

	GLuint vertex = Compile(vShaderCode, "VERTEX");
	GLuint fragment = Compile(fShaderCode, "FRAGMENT");

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);
	LinkCheck();

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(this->program);
}

// Private
std::string Shader::ParseShaderFile(const GLchar* sourcePath)
{
	std::ifstream shaderFile;
	shaderFile.open((sourcePath));

	std::string output;
	std::string line;

	if (shaderFile.is_open())
	{
		while (shaderFile.good())
		{
			getline(shaderFile, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	return output;
	/*
	std::string code;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(sourcePath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		code = shaderStream.str();
	}
	catch (std::ifstream::failure error)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	return code;
	*/
}

GLuint Shader::Compile(std::string& shaderCode, std::string type)
{
	GLuint shader;
	std::string path;

	if (type == "VERTEX")
	{
		path = vertexPath;
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == "FRAGMENT")
	{
		path = fragmentPath;
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	if (shader == 0)
	{
		std::cerr << "ERROR::" << type.c_str() << "SHADER::COMPILE::CREATE_SHADER_FAILED - " << path << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = shaderCode.c_str();
	shaderSourceStringLengths[0] = shaderCode.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	CompileCheck(shader, type);

	return shader;
}

void Shader::CompileCheck(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::" << type.c_str() << "SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::LinkCheck()
{
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}