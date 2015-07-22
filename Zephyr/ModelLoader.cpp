#include "ModelLoader.h"


ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

bool ModelLoader::LoadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals)
{
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> texCoordIndices;
	std::vector<unsigned int> normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempTexCoords;
	std::vector<glm::vec3> tempNormals;

	FILE* file = fopen(path, "r");

	if (file == NULL)
	{
		std::cerr << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_OPENED - " << path << std::endl;
		return false;
	}

	while (1)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
		{
			break;
		}

		// Vertices
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		// Texture coordinates
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 texCoord;
			fscanf(file, "%f %f\n", &texCoord.x, &texCoord.y);
			tempTexCoords.push_back(texCoord);
		}
		// Normals
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		// Faces
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], texCoordIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &texCoordIndex[0], &texCoordIndex[1], &texCoordIndex[2], &normalIndex[0], &normalIndex[1], &normalIndex[2]);

			if (matches != 9)
			{
				std::cerr << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ - " << path << std::endl;
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			texCoordIndices.push_back(texCoordIndex[0]);
			texCoordIndices.push_back(texCoordIndex[1]);
			texCoordIndices.push_back(texCoordIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

		unsigned int i;
		int size = vertexIndices.size();

		for (i = 0; i < size; i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = tempVertices[vertexIndex - 1];
			outVertices.push_back(vertex);
		}

		size = texCoordIndices.size();
		for (i = 0; i < size; i++)
		{
			unsigned int texCoordIndex = texCoordIndices[i];
			glm::vec2 texCoord = tempTexCoords[texCoordIndex - 1];
			outTexCoords.push_back(texCoord);
		}

		size = normalIndices.size();
		for (i = 0; i < size; i++)
		{
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = tempNormals[normalIndex - 1];
			outNormals.push_back(normal);
		}
	}
}