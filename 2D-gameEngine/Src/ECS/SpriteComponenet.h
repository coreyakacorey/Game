#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRectangle, destinationRectangle;

	bool animated = false;
	int frames = 0;
	int speed = 100;	//Delay between frames (ms)

public:
	SpriteComponent() = default;
	//Non-animated sprite constructor 
	SpriteComponent(const char* path) {
		setTex(path);
	}

	//Animated sprite constructor
	SpriteComponent(const char* path, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
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
		
		destinationRectangle.x = static_cast<int>(transform->position.x);
		destinationRectangle.y = static_cast<int>(transform->position.y);
		destinationRectangle.w = transform->width * transform->scale;
		destinationRectangle.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle);
	}
};
