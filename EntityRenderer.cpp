#include "EntityRenderer.h"

#include <iostream>


EntityRenderer::EntityRenderer() {
}

void EntityRenderer::init(RawModel& model, const std::string& file) {
}

EntityRenderer::~EntityRenderer() {
}

void EntityRenderer::load(Entity& entity) {
	entities.push_back(entity);
}

void EntityRenderer::free() {
	for (Entity& entity : entities) {
		entity.free();
	}
}

void EntityRenderer::initRenderer(Camera& camera) {
	GLuint error;
	for (Entity& entity : entities) {
		entity.getShader().Bind();
		entity.getShader().bindUniform("modelMatrix", entity.getTransform().getModel());
		entity.getShader().bindUniform("viewMatrix", camera.getViewMatrix());
		entity.getShader().bindUniform("projectionMatrix", camera.getProjectionMatrix());
		entity.getShader().bindUniform("material.Kd", glm::vec3(0.9, 0.9, 0.9f));
		entity.getShader().bindUniform("light.Ld", glm::vec3(1.0, 1.0, 1.0));
		entity.getShader().bindUniform("material.Ka", glm::vec3(0.2, 0.2, 0.2));
		entity.getShader().bindUniform("light.La", glm::vec3(0.9, 0.9, 0.9));
		entity.getShader().bindUniform("material.Ks", glm::vec3(1.0, 1.0, 1.0));
		entity.getShader().bindUniform("light.Ls", glm::vec3(1.0, 10.0, 1.0));
		entity.getShader().bindUniform("material.shininess", 20);
		entity.getShader().bindUniform("light.Position", glm::vec3(0.0, 10000.0, 0.0));
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}

		std::vector<Texture> textures = entity.getTextures();
		for (int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0);
			textures[i].bind();
		}

		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}
		glBindVertexArray(entity.getMesh().getVertexArrayObject());
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glDrawElements(GL_TRIANGLES, entity.getMesh().getDrawCount(), GL_UNSIGNED_INT, 0);
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}

		entity.getShader().Stop();
		
	}
}
