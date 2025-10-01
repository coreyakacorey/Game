#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y) {

	objectTexture = TextureManager::LoadTexture(texturesheet);

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
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectange, &destinationRectange);

}
