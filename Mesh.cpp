#include "Mesh.h"

#include <iostream>

#include "OBJloader.h"


Mesh::Mesh(RawModel& mode) {
}

void Mesh::initMesh(Vertex* vertices, GLuint numVertices, unsigned int* indices, GLuint numIndices) {
	m_drawCount = numIndices;

	/*std::cout << vertices[0].getPosition()[1] << std::endl;
	std::cout << vertices[1].getPosition()[1] << std::endl;*/

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numVertices, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_elementArrayBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementArrayBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])* numIndices, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertices[0].getNormals()) + sizeof(vertices[0].getTexCoord()), 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
}


void Mesh::initMesh(RawModel& model) {
	this->initMesh(model.vertices2Array(), model.getVerticesSize(), model.indices2Array(), model.getIndicesSize());
}

void Mesh::initMesh(Vertex* vertices, GLuint numVertices) {
	m_drawCount = numVertices;

	/*std::cout << vertices[0].getPosition()[1] << std::endl;
	std::cout << vertices[1].getPosition()[1] << std::endl;*/

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(1, &m_vertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*numVertices, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertices[0].getNormals()) + sizeof(vertices[0].getTexCoord()), 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 8 * sizeof(float), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &m_vertexArrayBuffer);
	glDeleteBuffers(1, &m_elementArrayBuffer);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}
