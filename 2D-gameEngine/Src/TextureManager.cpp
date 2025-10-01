#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* rend) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* text = SDL_CreateTextureFromSurface(rend, tempSurface);
	SDL_FreeSurface(tempSurface);

	return text;
}