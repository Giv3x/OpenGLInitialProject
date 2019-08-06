#include "Renderer.h"



Renderer::Renderer() {
}


Renderer::~Renderer() {
}


void Renderer::render(EntityRenderer& renderer, Camera& camera) {
	renderer.initRenderer(camera);
}
