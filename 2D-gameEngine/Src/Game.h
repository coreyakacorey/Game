#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int witdh, int height, bool fullscreen);

	void handelEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning;  }

	static SDL_Renderer* renderer;

private:
	int count = 0;
	bool isRunning;
	SDL_Window *window;
};


#endif /* Game_h */
