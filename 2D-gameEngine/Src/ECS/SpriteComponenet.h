#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRectangle, destinationRectangle;

	bool animated = false;
	int frames = 0;
	int speed = 100;	//Delay between frames (ms)

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	//Non-animated sprite constructor 
	SpriteComponent(const char* path) {
		setTex(path);
	}

	//Animated sprite constructor
	SpriteComponent(const char* path, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(1, 4, 100);
		Animation walk = Animation(0, 6, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

		setTex(path);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = transform->width;
		sourceRectangle.h = transform->height;
	}

	void update() override {

		if(animated){
			//Remainder of frames after delay multiplies by rectangle width
			sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		sourceRectangle.y = animIndex * transform->height;
		
		destinationRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destinationRectangle.y = static_cast<int>(transform->position.y)- Game::camera.y;
		destinationRectangle.w = transform->width * transform->scale;
		destinationRectangle.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
	}

	void Play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};
