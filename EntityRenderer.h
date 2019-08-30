#pragma once

#include "Entity.h"
#include "Camera.h"

class EntityRenderer
{
public:
	EntityRenderer();

	void load(Entity& entity);
	void initRenderer(Camera& camera);
	void init(RawModel& model, const std::string& file);

	void free();
	~EntityRenderer();

private:
	std::vector<Entity> entities;
};

