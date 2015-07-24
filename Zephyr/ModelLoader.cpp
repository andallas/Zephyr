#include "ModelLoader.h"


ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

bool ModelLoader::LoadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_OPENED - " << path << std::endl;
		file.close();
		return false;
	}

	if (!Parse(file, outVertices, outTexCoords, outNormals))
	{
		std::cerr << "ERROR::MODEL::FILE_NOT_SUCCESSFULLY_READ - " << path << std::endl;
		file.close();
		return false;
	}

	if (file.bad())
	{
		std::cerr << "ERROR::MODEL::BAD_FILE_READ - " << path << std::endl;
		file.close();
		return false;
	}

	return true;
}

bool ModelLoader::Parse(std::ifstream& file, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals)
{
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> texCoordIndices;
	std::vector<unsigned int> normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempTexCoords;
	std::vector<glm::vec3> tempNormals;

	std::vector<std::string> elements;
	std::string line;

	while (getline(file, line))
	{
		// Vertices
		if (line.substr(0, 2) == "v ")
		{
			glm::vec3 vertex;
			elements = Split(line, ' ');
			if (elements.size() != 4)
			{
				return false;
			}

			vertex.x = std::stof(elements[1]);
			vertex.y = std::stof(elements[2]);
			vertex.z = std::stof(elements[3]);
			tempVertices.push_back(vertex);
		}
		// Texture coordinates
		else if (line.substr(0, 2) == "vt")
		{
			glm::vec2 texCoord;
			elements = Split(line, ' ');
			if (elements.size() != 3)
			{
				return false;
			}

			texCoord.x = std::stof(elements[1]);
			texCoord.y = std::stof(elements[2]);
			tempTexCoords.push_back(texCoord);
		}
		// Normals
		else if (line.substr(0, 2) == "vn")
		{
			glm::vec3 normal;
			elements = Split(line, ' ');
			if (elements.size() != 4)
			{
				return false;
			}

			normal.x = std::stof(elements[1]);
			normal.y = std::stof(elements[2]);
			normal.z = std::stof(elements[3]);
			tempNormals.push_back(normal);
		}
		// Faces
		else if (line.substr(0, 2) == "f ")
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], texCoordIndex[3], normalIndex[3];

			elements = Split(line, ' ');
			if (elements.size() != 5)
			{
				return false;
			}

			elements.erase(elements.begin());
			int length = elements.size();
			std::vector<std::string> temp;
			std::vector<std::string> indices;

			for (int i = 0; i < length; i++)
			{
				temp = Split(elements[i], '/');

				if (elements.size() != 4)
				{
					return false;
				}

				indices.insert(indices.end(), temp.begin(), temp.end());
			}

			if (indices.size() != 12)
			{
				return false;
			}

			vertexIndices.push_back(std::stof(indices[0]));
			vertexIndices.push_back(std::stof(indices[1]));
			vertexIndices.push_back(std::stof(indices[2]));

			texCoordIndices.push_back(std::stof(indices[3]));
			texCoordIndices.push_back(std::stof(indices[4]));
			texCoordIndices.push_back(std::stof(indices[5]));

			normalIndices.push_back(std::stof(indices[6]));
			normalIndices.push_back(std::stof(indices[7]));
			normalIndices.push_back(std::stof(indices[8]));
		}

		if (tempVertices.size() <= 0)
		{
			// Line does not include important content
			return true;
		}

		unsigned int i;
		int size = vertexIndices.size();

		for (i = 0; i < size; i++)
		{
			glm::vec3 vertex = tempVertices[vertexIndices[i] - 1];
			outVertices.push_back(vertex);
		}

		size = texCoordIndices.size();
		for (i = 0; i < size; i++)
		{
			glm::vec2 texCoord = tempTexCoords[texCoordIndices[i] - 1];
			outTexCoords.push_back(texCoord);
		}

		size = normalIndices.size();
		for (i = 0; i < size; i++)
		{
			glm::vec3 normal = tempNormals[normalIndices[i] - 1];
			outNormals.push_back(normal);
		}
	}

	return true;
}

std::vector<std::string> ModelLoader::Split(std::string str, char delimeter)
{
	std::vector<std::string> elements;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delimeter))
	{
		if (!item.empty())
		{
			elements.push_back(item);
		}
	}
	return elements;
}