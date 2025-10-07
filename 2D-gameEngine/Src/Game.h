#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class ColliderComponent;

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

	static void AddTile(int srcX,int srcY, int xpos, int ypos);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int count = 0;
	bool isRunning;
	SDL_Window *window;
};


#endif /* Game_h */

