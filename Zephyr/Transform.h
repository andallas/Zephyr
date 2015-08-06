#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scl = glm::vec3(1.0, 1.0, 1.0)) : position(pos), rotation(rot), scale(scl) { }

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(position);
		glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
		glm::mat4 sclMatrix = glm::scale(scale);

		return posMatrix * rotMatrix * sclMatrix;
	}

	inline glm::vec3& GetPos() { return position; }
	inline glm::vec3& GetRot() { return rotation; }
	inline glm::vec3& GetScale() { return scale; }

	inline void SetPos(const glm::vec3& pos) { position = pos; }
	inline void SetRot(const glm::vec3& rot) { rotation = rot; }
	inline void SetScale(const glm::vec3& scl) { scale = scl; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

#endif