#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>

#include "RawModel.h"

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
	Mesh(RawModel& model);
	GLuint getVertexArrayObject() { return m_vertexArrayObject; }
	GLuint getDrawCount() { return m_drawCount; }
	void initMesh(RawModel& model);
	void initMesh(Vertex* vertices, GLuint numVertices, unsigned int* indices, GLuint numIndices);
	void initMesh(Vertex* vertices, GLuint numVertices);
	virtual ~Mesh();

private:
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffer;
	GLuint m_elementArrayBuffer;
	GLuint m_drawCount;
};

