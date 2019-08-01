#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>

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

enum BufferPositions {
	POSITION_VB,
	TEXCOORDS_VB,
	NORMAL_VB,

	NUM_BUFFERS
};

class Mesh
{
public:
	Mesh() {}
	Mesh(Vertex* vertices, GLuint numVertices, int* indices, GLuint numIndices);
	Mesh(const std::string& fileName);
	virtual ~Mesh();
	void Draw();

private:
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	GLuint m_elementArrayBuffer;
	GLuint m_drawCount;

	void initMesh(Vertex* vertices, GLuint numVertices, unsigned int* indices, GLuint numIndices);
};

