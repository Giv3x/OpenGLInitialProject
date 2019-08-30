#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "RawModel.h"
#include "OBJloader.h"


class Entity
{
public:
	Entity();
	Entity(RawModel& model, Texture& texture, Shader& shader);
	Entity(const std::string& modelLoc, const std::string& textureLoc, const std::string& shaderLoc);
	
	void loadTexture(const std::string& file);
	RawModel& getModel() { return model; }
	Transform& getTransform() { return transform; }
	Mesh& getMesh() { return mesh; }
	Shader& getShader() { return shader; }
	std::vector<Texture>& getTextures() { return textures; }

	void free();
	~Entity();

private:
	Mesh mesh;
	RawModel model;
	Transform transform;
	Shader shader;
	std::vector<Texture> textures;
};

