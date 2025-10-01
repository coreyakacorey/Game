#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* rend, int x, int y) {

	renderer = rend;
	objectTexture = TextureManager::LoadTexture(texturesheet, rend);

	xpos = x;
	ypos = y;
}

void GameObject::Update() {
	
	xpos++;
	ypos++;

	sourceRectange.h = 32;
	sourceRectange.w = 32;
	sourceRectange.x = 0;
	sourceRectange.y = 0;

	destinationRectange.x = xpos;
	destinationRectange.y = ypos;
	destinationRectange.w = sourceRectange.w;
	destinationRectange.h = sourceRectange.h;

}

void GameObject::Render() {
	SDL_RenderCopy(renderer, objectTexture, &sourceRectange, &destinationRectange);
}