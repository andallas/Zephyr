#include "Mesh.h"


Mesh::Mesh(const char* path)
{
	std::vector<glm::vec3> v;
	std::vector<glm::vec2> tc;
	std::vector<glm::vec3> n;

	if (!ModelLoader::LoadOBJ(path, v, tc, n))
	{
		std::cerr << "ERROR::MESH::MESH_FAILED_TO_LOAD" << std::endl;
	}

	for (int i = 0; i < v.size(); i++)
	{
		this->vertices.push_back(Vertex(v[i], n[i], tc[i]));
	}

	this->SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->textures = textures;
	this->SetupMesh();
}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> texCoords, std::vector<Texture> textures)
{
	for (int i = 0; i < this->vertices.size(); i++)
	{
		this->vertices.push_back(Vertex(vertices[i], normals[i], texCoords[i]));
	}
	this->textures = textures;

	this->SetupMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->_VAO);
	glDeleteBuffers(1, &this->_VBO);
}

void Mesh::Bind()
{
	glBindVertexArray(this->_VAO);

	BindTexture(GL_TEXTURE0, this->textures[0].id);
	BindTexture(GL_TEXTURE1, this->textures[1].id);
	BindTexture(GL_TEXTURE2, this->textures[2].id);
}

// Private
void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &this->_VAO);
	glGenBuffers(1, &this->_VBO);

	glBindVertexArray(this->_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	// Tex coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::BindTexture(GLint textureLocation, GLuint textureID)
{
	glActiveTexture(textureLocation);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Mesh::UnBindTexture(GLint textureLocation)
{
	glActiveTexture(textureLocation);
	glBindTexture(GL_TEXTURE_2D, 0);
}