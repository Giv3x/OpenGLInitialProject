#include "OBJloader.h"

#include <fstream>
#include <iostream>

OBJloader::OBJloader() {
}

RawModel OBJloader::load(const char* file) {
	std::ifstream str(file);
	std::string line;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;

	std::vector<Vertex> vertexData;
	std::vector<unsigned int> indices;

	std::vector<std::string> strVector;
	int i = 0;
	while (std::getline(str, line)) {
		strVector = split(line, ' ');
		i++;
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
			std::cout << "ups" << std::endl;
		}
		std::cout << i << std::endl;
	}

	do {
		if (line[0] != 'f')
			break;
		std::vector<std::string> indexData = split(line, ' ');
		processVertex(indexData[1], vertices, textures, normals, indices, vertexData);
		processVertex(indexData[2], vertices, textures, normals, indices, vertexData);
		processVertex(indexData[3], vertices, textures, normals, indices, vertexData);
	} while (std::getline(str, line));

	RawModel model(vertexData, indices);

	//Mesh mesh(&vertexData[0], vertexData.size(), &indices[0], indices.size());
	//Mesh mesh(testVerticesData, 3, testIndicesData, 3);

	return model;
}


void OBJloader::processVertex(std::string& indexData, std::vector<glm::vec3>& v, std::vector<glm::vec2>& t,
		std::vector<glm::vec3>& n, std::vector<unsigned int>& indices, std::vector<Vertex>& vertexData) {
	std::vector<std::string> ind = split(indexData, '/');
	
	int currentVertex = stoi(ind[0]) - 1;
	int currentTexture = stoi(ind[1]) - 1;
	int currentNormal = stoi(ind[2]) - 1;

	indices.push_back(currentVertex);
	vertexData[currentVertex] = Vertex(v[currentVertex], t[currentTexture], n[currentNormal]);
}


OBJloader::~OBJloader() {
}
