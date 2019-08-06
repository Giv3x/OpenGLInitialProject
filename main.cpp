#include <iostream>
#include <GL\glew.h>
#include <map>

#include "Display.h"
#include "Camera.h"
#include "Entity.h"
#include "Renderer.h"

#include "util.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace std;

int main(int argc, char** argv) {
	Display display(WIDTH, HEIGHT, "test window");
	Entity entity("res/objs/tree.obj", "res/textures/tree.png", "res/shaders/basicShader");
	Camera camera(glm::vec3(0, 0, -10), 70.f, 1200 / 800, 0.1f, 1000.f);
	EntityRenderer entityRenderer;
	Renderer renderer;

	glm::ivec2 mouseLocation;
	map<int, bool> keyPress;

	entityRenderer.load(entity);

	while (!display.isClosed()) {
		GLuint error;
		while ((error = glGetError()) != GL_NO_ERROR) {
			std::cout << error << std::endl;
		}
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(entityRenderer, camera);

		SDL_Event e;

		display.update(e);	
		SDL_Delay(1);

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
			camera.move(camera.getForward(), 0.01);
		}
		if (keyPress[SDLK_s]) {
			camera.move(-camera.getForward(), 0.01);
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