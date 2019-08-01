#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(glm::vec3& pos = glm::vec3(), glm::vec3& rot = glm::vec3(), glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: position(pos), rotation(rot), scale(scale) {};
	~Transform() {};

	glm::mat4 getModel() {
		glm::mat4 transform = glm::translate(position);
		
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotate = rotZ*rotY*rotX;

		glm::mat4 scaleMatrix = glm::scale(scale);

		return transform*rotate*scaleMatrix;
	}

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	glm::vec3& getScale() { return scale; }

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

private:
};

