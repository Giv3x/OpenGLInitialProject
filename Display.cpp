#include "Display.h"
#include <GL\glew.h>
#include <iostream>


Display::Display(int width, int height, const std::string& name) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	

	GLuint error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cout << error << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}


Display::~Display() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


void Display::close() {
	m_isClosed = true;
}


void Display::update(SDL_Event& e) {
	SDL_GL_SwapWindow(m_window);
}


bool Display::isClosed() {
	return m_isClosed;
}


SDL_Window* Display::getWindow() {
	return m_window;
}