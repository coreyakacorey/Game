#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;
	int type;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	TransformComponent* transform;

	ColliderComponent(std::string t) {
		tag = t;
	}

	//Optional, switch on tag
	ColliderComponent(std::string t, int xpos, int ypos, int size, int type){
		tag = t;
		type = type;

		switch(type){
			//Full tile
			case 1:	
				collider.x = xpos;
				collider.y = ypos;
				collider.h = collider.w = size;
				break;
			//Bottom half
			case 2:
				collider.x = xpos + (size / 2);
				collider.y = ypos + (size / 2);
				collider.h = collider.w = (size / 2);
				break;
			//Top half
			case 3:
				break;
			//Left half
			case 4:
				break;
			//Right half
			case 5:
				break;
			default:
				break;
		}
		/*collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;*/
	}

	//Optional, switch on tag
	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		switch(type){
			//Full tile
			case 1:	
				tex = TextureManager::LoadTexture("assets/colTex.png");
				break;
			//Bottom half
			case 2:
				//tex = TextureManager::LoadTexture("assets/colTexBH.png");
				break;
			//Top half
			case 3:
				break;
			//Left half
			case 4:
				break;
			//Right half
			case 5:
				break;
			default:
				break;
		}

		//tex = TextureManager::LoadTexture("assets/colTex.png");
		srcR = {0, 0, 32, 32};
		destR = {collider.x, collider.y, collider.w, collider.h};
	}

	void update() override {
		if(tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		//update position due to camera follow
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;
	}

void draw() override{
	TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}
};
