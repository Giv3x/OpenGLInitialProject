#pragma once

#include "EntityRenderer.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	void render(EntityRenderer& renderer, Camera& camera);

	~Renderer();
};

