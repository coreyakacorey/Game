#pragma once
#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		//Get keybaord state
		const Uint8* ks = SDL_GetKeyboardState(nullptr);

		//Movement intent
		int x = (ks[SDL_SCANCODE_D] ? 1 : 0) - (ks[SDL_SCANCODE_A] ? 1 : 0);
		int y = (ks[SDL_SCANCODE_S] ? 1 : 0) - (ks[SDL_SCANCODE_W] ? 1 : 0);
	
		//Apply velocity
		transform->velocity.x = static_cast<float>(x);
		transform->velocity.y = static_cast<float>(y);

		//Scale diagonal speed
		if (x && y) {
			const float invSqrt2 = 0.707f;
			transform->velocity.x *= invSqrt2;
			transform->velocity.y *= invSqrt2;
		}

		//Sprite direction
		if (transform->velocity.x < 0) {
			sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		}
		else if (transform->velocity.x > 0) {
			sprite->spriteFlip = SDL_FLIP_NONE;
		}

		//Sprite animations
		if (x != 0 || y != 0) {
			sprite->Play("Walk");
		}
		else {
			sprite->Play("Idle");
		}

		if (ks[SDL_SCANCODE_SPACE]) {
			Vector2D vel;
			if (sprite->spriteFlip == SDL_FLIP_NONE) {
				vel = Vector2D(2, 0);
			}
			else {
				vel = Vector2D(-2, 0);
			}
			Game::assets->CreateProjectile(Vector2D(transform->position.x + (transform->width / 2), transform->position.y + (transform->height / 2)), vel, 200, 1, "projectile");
		}

	}
};
