#include "Mesh.h"

#include <iostream>

#include "OBJloader.h"


Mesh::Mesh(const std::string& filename) {
	OBJloader loader;
	RawModel model = loader.load(filename.c_str());

	//this->initMesh(model.vertices2Array(), model.getIndicesSize(), model.indices2Array(), model.getIndicesSize());
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

Mesh::~Mesh() {
	glDeleteBuffers(1, &m_vertexArrayBuffer);
	glDeleteBuffers(1, &m_elementArrayBuffer);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}