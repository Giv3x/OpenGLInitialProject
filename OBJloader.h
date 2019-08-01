#pragma once
#include "util.h"
#include <glm\glm.hpp>
#include "Mesh.h"

class OBJloader
{
public:
	OBJloader();
	~OBJloader();
	Mesh load(const char* file);

protected:
private:
	void processVertex(std::string& vertices, std::vector<glm::vec3>& v, std::vector<glm::vec2>& t, 
		std::vector<glm::vec3>& n, std::vector<int>& indices, std::vector<Vertex>& vertexData);
};

