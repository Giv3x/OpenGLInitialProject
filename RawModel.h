#pragma once

#include <glm\glm.hpp>

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoords = glm::vec2(0, 0), const glm::vec3& normals = glm::vec3(0,0,0)) {
		positions = pos;
		this->texCoords = texCoords;
		this->normals = normals;
	}

	glm::vec3& getPosition() {
		return positions;
	}

private:
	glm::vec3 positions;
	glm::vec2 texCoords;
	glm::vec3 normals;
};

class RawModel
{
public:
	RawModel();
	~RawModel();

private:
	Vertex* vertices = nullptr;
};

