#ifndef Game_h
#define Game_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
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

	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles
		//Can have up to 32 groups
	};

private:
	int count = 0;
	SDL_Window *window;
};


#endif /* Game_h */






