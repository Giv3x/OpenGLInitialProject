#pragma once

#include <glm\glm.hpp>
#include <vector>

#include "Texture.h"

class Vertex {
public:
	Vertex(glm::vec3& pos, glm::vec2& texCoords = glm::vec2(0, 0), glm::vec3& normals = glm::vec3(0, 0, 0)) {
		positions = pos;
		this->texCoords = texCoords;
		this->normals = normals;
	}

	Vertex() {}
	~Vertex() {}

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
	RawModel(unsigned int numVertices, unsigned int numIndices = 0);
	RawModel(const std::vector<Vertex>& v, const std::vector<unsigned int>& i);
	void loadData(const std::vector<Vertex>& v, const std::vector<unsigned int>& i);
	void loadTexture(const std::string& file);
	~RawModel();

	unsigned int getVerticesSize() { return vertices.size(); }
	unsigned int getIndicesSize() { return indices.size(); }
	Vertex* vertices2Array() { return &vertices[0]; }
	unsigned int* indices2Array() { return &indices[0]; }
	std::vector<Vertex>* getVertices() { return &vertices; }
	std::vector<unsigned int>* getIndices() { return &indices; }

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

