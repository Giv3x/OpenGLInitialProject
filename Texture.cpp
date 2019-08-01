#include "Texture.h"
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& filename) {
	unsigned char* image = stbi_load(filename.c_str(), &m_width, &m_height, &m_numComponents, 4);

	if (image == NULL) {
		std::cerr << "unable to load the texture data" << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, GL_FALSE, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}