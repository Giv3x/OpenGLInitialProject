#include "OBJloader.h"

#include <fstream>

OBJloader::OBJloader() {
}

Mesh OBJloader::load(const char* file) {
	std::ifstream str(file);
	std::string line;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;

	std::vector<Vertex> vertexData;
	std::vector<int> indices;

	std::vector<std::string> strVector;

	while (std::getline(str, line)) {
		strVector = split(line, ' ');
		if (strVector[0] == "v") {
			vertices.push_back(glm::vec3(stof(strVector[1]), stof(strVector[2]), stof(strVector[3])));
		}
		else if (strVector[0] == "vt") {
			textures.push_back(glm::vec2(stof(strVector[1]), stof(strVector[2])));
		}
		else if (strVector[0] == "vn") {
			normals.push_back(glm::vec3(stof(strVector[1]), stof(strVector[2]), stof(strVector[3])));
		}
		else if (strVector[0] == "f") {
			vertexData.resize(vertices.size());
			break;
		}
	}

	do {
		if (line[0] != 'f')
			break;
		std::vector<std::string> indexData = split(line, ' ');
		processVertex(indexData[1], vertices, textures, normals, indices, vertexData);
		processVertex(indexData[2], vertices, textures, normals, indices, vertexData);
		processVertex(indexData[3], vertices, textures, normals, indices, vertexData);
	} while (std::getline(str, line));

	Vertex testVerticesData[3];
	for (int i = 0; i < vertexData.size(); i++) {
		testVerticesData[i] = vertexData[i];
	}

	int testIndicesData[3];
	for (int i = 0; i < indices.size(); i++) {
		testIndicesData[i] = indices[i];
	}

	//Mesh mesh(&vertexData[0], vertexData.size(), &indices[0], indices.size());
	Mesh mesh(testVerticesData, 3, testIndicesData, 3);

	return mesh;
}


void OBJloader::processVertex(std::string& indexData, std::vector<glm::vec3>& v, std::vector<glm::vec2>& t,
		std::vector<glm::vec3>& n, std::vector<int>& indices, std::vector<Vertex>& vertexData) {
	std::vector<std::string> ind = split(indexData, '/');
	
	int currentVertex = stoi(ind[0]) - 1;
	int currentTexture = stoi(ind[1]) - 1;
	int currentNormal = stoi(ind[2]) - 1;

	indices.push_back(currentVertex);
	vertexData[currentVertex] = Vertex(v[currentVertex], t[currentTexture], n[currentNormal]);
}


OBJloader::~OBJloader() {
}
