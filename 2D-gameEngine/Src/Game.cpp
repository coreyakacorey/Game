#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "CombatManager.h"
#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

const int width = 800;
const int height = 640;

SDL_Rect Game::camera = {0,0, width * 2, height * 2};
AssetManager* Game::assets = new AssetManager(&manager);
CombatManager* combat = new CombatManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& enemy2(manager.addEntity());
//Entity* enemy3 = &manager.addEntity();
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
	assets->AddTexture("enemy", "assets/Enemy.png");

	assets->AddFont("arial", "assets/arial.ttf", 16);

	map = new Map("terrain", 3, 32);
	map->loadMap("assets/Map25x20text.txt", 25, 20);

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addComponent<StatsComponent>(100, 1);
	player.addGroup(groupPlayers);

	SDL_Color white = { 255, 255, 255, 255 };

	label.addComponent<UILabel>(10, 10, "Test String", "arial", white);

	enemy.addComponent<TransformComponent>(350, 348);
	enemy.addComponent<SpriteComponent>("enemy");
	enemy.addComponent<ColliderComponent>("enemy");
	enemy.addComponent<StatsComponent>(5, 1, 5);
	enemy.addGroup(groupEnemies);

	enemy2.addComponent<TransformComponent>(500, 500);
	enemy2.addComponent<SpriteComponent>("enemy");
	enemy2.addComponent<ColliderComponent>("enemy2");
	enemy2.addComponent<StatsComponent>(5, 1, 4);
	enemy2.addGroup(groupEnemies);
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
	int playerHealth = player.getComponent<StatsComponent>().curHealth;
	
	/*if (enemy.hasComponent<StatsComponent>() == NULL) {
		std::stringstream ss;
		ss << "enemy Dead";
		label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
	}*/

	//map->LoadMap();
	manager.update();

	std::stringstream ss;
	ss << "Lvl: " << player.getComponent<StatsComponent>().exp;
	label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
	
	for(auto& c : colliders){
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		std::string tag = c->getComponent<ColliderComponent>().tag;
		auto& enemyC = enemy.getComponent<ColliderComponent>().collider;
		auto& enemyC2 = enemy2.getComponent<ColliderComponent>().collider;

		if (tag == "projectile") {
			if (enemy.hasComponent<StatsComponent>() != NULL) {
				if (Collision::AABB(cCol, enemyC)) {
					combat->queueHit(&enemy, c, &player, 1);
					std::cout << "Enemy hit" << std::endl;
					/*std::stringstream ss;
					ss << "enemy health: " << enemy.getComponent<StatsComponent>().curHealth;
					label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");*/
				}
			}
			if (enemy2.hasComponent<StatsComponent>() != NULL) {
				if (Collision::AABB(cCol, enemy2.getComponent<ColliderComponent>().collider)) {
					combat->queueHit(&enemy2, c, &player, 1);
					/*std::cout << "Enemy hit" << std::endl;
					std::stringstream ss;
					ss << "enemy2aw health: " << enemy2.getComponent<StatsComponent>().curHealth;
					label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");*/
				}
			}
		}

		if (tag != "projectile") {
			switch (Collision::AABBint(cCol, playerCol)) {
			case 0:
				break;
			case 1:
				player.getComponent<TransformComponent>().position.y = playerPos.y + 1;
				break;
			case 2:
				player.getComponent<TransformComponent>().position.x = playerPos.x - 1;
				break;
			case 3:
				player.getComponent<TransformComponent>().position.y = playerPos.y - 1;
				break;
			case 4:
				player.getComponent<TransformComponent>().position.x = playerPos.x + 1;
				break;
			default:
				break;

			}
		}
	}

	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

	//Stop camera from scrolling out of bounds
	if(camera.x < 0) camera.x = 0;
	if(camera.y < 0) camera.y = 0;
	if(camera.x > camera.w) camera.x = camera.w;
	if(camera.y > camera.h) camera.y = camera.h;

	combat->endOfFrameResolve();
	manager.refresh();
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
	for(auto& e : enemies){
		e->draw();
	}

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

















