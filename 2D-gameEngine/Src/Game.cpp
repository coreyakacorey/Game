#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"


SDL_Renderer* Game::renderer = nullptr;
Map* map;
SDL_Event Game::event;

SDL_Rect Game::camera = {0,0, 800, 640};

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

const char* mapfile = "assests/terrain_ss.png"

//Lists of objests in each group
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}

	map = new Map();

	Map::loadMap("assests/map.map", 25, 20);

	//player.addComponent<TransformComponent>(284,64);
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assests/Turtle_animations.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	enemy.addComponent<TransformComponent>(384, 128);
	enemy.addComponent<SpriteComponent>("assests/Enemy.png");
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addGroup(groupEnemies);
}

void Game::handelEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	//map->LoadMap();
	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//Stop camera from scrolling out of bounds
	if(camera.x < 0) camera.x = 0;
	if(camera.y < 0) camera.y = 0;
	if(camera.x > camera.w) camera.x = camera.w;
	if(camera.y > camera.h) camera.y = camera.h;
	
}

void Game::render()
{
	SDL_RenderClear(Game::renderer);
	for(auto& t : tiles){
		t->draw();
	}
	for(auto& p : players){
		p->draw();
	}
	for(auto& e : enemies){
		e->draw();
	}
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}













