#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <string>


class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	static bool LoadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals);

private:
	static bool Parse(std::ifstream& file, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals);
	static std::vector<std::string> Split(std::string str, char delimeter);
};

#endif