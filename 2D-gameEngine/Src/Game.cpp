#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

const int width = 800;
const int height = 640;

SDL_Rect Game::camera = {0,0, width * 2, height * 2};
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& label(manager.addEntity());

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

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	assets->AddTexture("terrain", "assets/Terrain.png");
	assets->AddTexture("player", "assets/Turtle_animations.png");
	assets->AddTexture("projectile", "assets/Proj.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);

	map->loadMap("assets/Map25x20text.txt", 25, 20);

	//player.addComponent<TransformComponent>(284,64);
	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	//Add health component
	//player.addComponent<HealthComponent>(100);
	player.addGroup(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };

	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

	enemy.addComponent<TransformComponent>(384, 128);
	enemy.addComponent<SpriteComponent>("enemy");
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addGroup(groupEnemies);

	assets->CreateProjectile(Vector2D(100, 100), Vector2D(2, 0), 200, 1, "projectile");
	assets->CreateProjectile(Vector2D(400, 320), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 300), Vector2D(2, 1), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(400, 300), Vector2D(2, -1), 200, 2, "projectile");
}

//Lists of objests in each group
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerVel = player.getComponent<TransformComponent>().velocity;
	int playerHealth = player.getComponent<HealthComponent>().curHealth;
	
	std::stringstream ss;
	ss << "Player velocity: " << playerVel;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");


	//map->LoadMap();
	manager.refresh();
	manager.update();

	for(auto& c : colliders){
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		
		/*if (Collision::AABB(cCol, playerCol)) {
			player.getComponent<TransformComponent>().position.x = playerPos.x;
			player.getComponent<TransformComponent>().position.y = playerPos.y;
			//std::cout << "Player: " << playerPos.x << " " << playerPos.y <<  std::endl;
		}*/

		switch (Collision::AABBint(cCol, playerCol)) {
		case 0:
			break;
		case 1:
			std::cout << "top" <<  std::endl;
			player.getComponent<TransformComponent>().position.y = playerPos.y + 1;
			break;
		case 2:
			std::cout << "right" << std::endl;
			player.getComponent<TransformComponent>().position.x = playerPos.x - 1;
			break;
		case 3:
			std::cout << "bottom" << std::endl;
			player.getComponent<TransformComponent>().position.y = playerPos.y - 1;
			break;
		case 4:
			player.getComponent<TransformComponent>().position.x = playerPos.x + 1;
			break;
		default:
			break;

		}

		/*if (Collision::AABBint(cCol, playerCol) != 0) {
			player.getComponent<TransformComponent>().position.x = playerPos.x;
			player.getComponent<TransformComponent>().position.y = playerPos.y;
			//std::cout << "Player: "  <<  std::endl;
		}*/
	}

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

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
	for(auto& c : colliders){
		c->draw();
	}
	for(auto& p : players){
		p->draw();
	}
	for (auto& p : projectiles){
		p->draw();
	}
	/*for(auto& e : enemies){
		e->draw();
	}*/

	label.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}















