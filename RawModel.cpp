#include "RawModel.h"



RawModel::RawModel() {
}


RawModel::RawModel(unsigned int numVertices, unsigned int numIndices) {
	vertices.resize(numVertices);
	indices.resize(numIndices);
}


RawModel::RawModel(const std::vector<Vertex>& v, const std::vector<unsigned int>& i) {
	vertices = v;
	indices = i;
}


void RawModel::loadData(const std::vector<Vertex>& v, const std::vector<unsigned int>& i) {
	vertices = v;
	indices = i;
}

RawModel::~RawModel() {
}


void RawModel::loadTexture(const std::string& file) {
	Texture texture(file);
}
