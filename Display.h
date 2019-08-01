#pragma once
#include <string>
#include <SDL2\SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& name);
	void update(SDL_Event& e);
	void close();
	bool isClosed();
	SDL_Window* getWindow();
	virtual ~Display();
protected:
private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed= false;
};

