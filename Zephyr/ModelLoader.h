#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	static bool LoadOBJ(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTexCoords, std::vector<glm::vec3>& outNormals);
};

#endif