#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture() {}
	Texture(const std::string& filename);
	void initTexture(const std::string& filename);
	void bind();
	void free();
	~Texture();

private:
	GLuint m_texture;
	int m_width;
	int m_height;
	int m_numComponents;
};

