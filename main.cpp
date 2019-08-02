#include <iostream>
#include <GL\glew.h>
#include <map>

#include "Display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "OBJloader.h"

#include "util.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace std;

int main(int argc, char** argv) {
	Display display(WIDTH, HEIGHT, "test window");
	Shader shader("res/shaders/basicShader");

	Vertex vertices[] = { Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f,1.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.5f,0.0f)),
	};

	int indices[] = { 0, 1, 2 };
	float counter = 0;
	glm::ivec2 mouseLocation;

	glm::vec4 outerColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glm::vec4 innerColor(1.0f, 1.0f, 0.75f, 1.0f);
	GLfloat innerRadius = 0.25f, outerRadius = 0.45f;

	//Mesh mesh(vertices, 3, indices, 3);
	Texture bricksTexture("res/textures/bricks.jpg");
	//Texture bricksTexture("res/textures/tree.png");
	Camera camera(glm::vec3(0, 0, -10), 70.f, 1200 / 800, 0.1f, 1000.f);
	Transform model;

	//Mesh mesh = obj.load("res/objs/triangle.obj");
	//Mesh mesh("res/objs/monkey3.obj");
	Mesh mesh("res/objs/monkey3.obj");

	map<int, bool> keyPress;

	while (!display.isClosed()) {
		/*GLuint error;
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}*/
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float sinCounter = sinf(counter);
		float absSinCounter = abs(sinCounter);

		//model.rotation.z = counter;
		//model.position.x = sinCounter;
		//model.position.x = sinCounter*10;
		//model.position.z = sinCounter*10;
		model.rotation.y = sinCounter;

		shader.Bind();
		shader.bindUniform("outerColor", outerColor);
		shader.bindUniform("innerColor", innerColor);
		shader.bindUniform("innerRadius", innerRadius);
		shader.bindUniform("outerRadius", outerRadius);
		shader.bindUniform("modelMatrix", model.getModel());
		shader.bindUniform("viewProjectionMatrix", camera.getViewProjection());

		bricksTexture.bind();
		mesh.Draw();

		SDL_Event e;

		display.update(e);	
		SDL_Delay(1);
		counter += 0.009f;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				display.close();
			if (e.type == SDL_KEYDOWN)
				keyPress[e.key.keysym.sym] = true;
			if (e.type == SDL_KEYUP)
				keyPress[e.key.keysym.sym] = false;
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				keyPress[e.button.button] = true;
				if (e.button.button == SDL_BUTTON_RIGHT) {
					SDL_ShowCursor(SDL_DISABLE);
					SDL_WarpMouseInWindow(display.getWindow(), WIDTH / 2, HEIGHT / 2);
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				keyPress[e.button.button] = false;
				if (e.button.button == SDL_BUTTON_RIGHT) {
					SDL_ShowCursor(SDL_ENABLE);
				}
			}

		}


		if (keyPress[SDLK_a]) {
			camera.move(camera.getLeft(), 0.01);
		}
		if (keyPress[SDLK_d]) {
			camera.move(camera.getRight(), 0.01);
		}
		if (keyPress[SDLK_w]) {
			camera.move(glm::vec3(0, 0, 1), 0.01);
		}
		if (keyPress[SDLK_s]) {
			camera.move(glm::vec3(0, 0, -1), 0.01);
		}
		if (keyPress[SDLK_UP]) {
			camera.rotateY(-0.1f);
		}
		if (keyPress[SDLK_DOWN]) {
			camera.rotateY(0.1f);
		}
		if (keyPress[SDLK_LEFT]) {
			camera.rotateX(0.1f);
		}
		if (keyPress[SDLK_RIGHT]) {
			camera.rotateX(-0.1f);
		}
		if(keyPress[SDL_BUTTON_RIGHT]) {
			SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
			camera.rotateX((mouseLocation.x - WIDTH/2)/-100.f);
			camera.rotateY((mouseLocation.y - HEIGHT/2)/100.f);
			SDL_WarpMouseInWindow(display.getWindow(), WIDTH / 2, HEIGHT / 2);
		}
				
	}

	return 0;
}