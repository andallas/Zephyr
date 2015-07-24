#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ModelLoader.h"


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	Vertex() : Position(), Normal(), TexCoords() {}
	Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 coords) : Position(pos), Normal(norm), TexCoords(coords) {}
};

struct Texture
{
	enum class TextureType
	{
		Diffuse, Specular, Emission
	};

	GLuint id;
	TextureType type;

	Texture() : id(), type() {}
	Texture(GLuint _id, TextureType _type) : id(_id), type(_type) {}
};

class Mesh
{
public:
	Mesh(const char* path);
	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures);
	Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords, std::vector<Texture> textures);
	~Mesh();
	void Bind();

	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

private:
	void SetupMesh();
	void BindTexture(GLint textureLocation, GLuint textureID);
	void UnBindTexture(GLint textureLocation);

	GLuint _VAO;
	GLuint _VBO;
};

#endif