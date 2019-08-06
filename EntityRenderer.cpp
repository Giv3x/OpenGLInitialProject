#include "EntityRenderer.h"


EntityRenderer::EntityRenderer() {
}

void EntityRenderer::init(RawModel& model, const std::string& file) {
}

EntityRenderer::~EntityRenderer() {
}

void EntityRenderer::load(Entity& entity) {
	entities.push_back(entity);
}

void EntityRenderer::initRenderer(Camera& camera) {
	for (Entity& entity : entities) {
		entity.getShader().Bind();
		entity.getShader().bindUniform("modelMatrix", entity.getTransform().getModel());
		entity.getShader().bindUniform("viewProjectionMatrix", camera.getViewProjection());

		std::vector<Texture> textures = entity.getTextures();
		for (int i = 0; i < textures.size(); i++)
			textures[i].bind();

		glBindVertexArray(entity.getMesh().getVertexArrayObject());
		glDrawElements(GL_TRIANGLES, entity.getMesh().getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
