#include "Entity.h"



Entity::Entity() {
}


Entity::Entity(RawModel& model, Texture& texture, Shader& shader) {
	this->mesh.initMesh(model);
	this->model = model;
	this->textures.push_back(texture);
	this->shader = shader;
}


Entity::Entity(const std::string& modelLoc, const std::string& textureLoc, const std::string& shaderLoc) {
	OBJloader loader;

	model = loader.load(modelLoc.c_str());
	mesh.initMesh(model);
	shader.initShader(shaderLoc);
	textures.push_back(Texture(textureLoc));
}


void Entity::loadTexture(const std::string& file) {
	textures.push_back(Texture(file));
}


Entity::~Entity() {
}

void Entity::free() {
	for (int i = 0; i < textures.size(); i++) {
		textures[i].free();
	}

	shader.free();
	mesh.free();
}
