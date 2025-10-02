#pragma once

#include "Game.h"

class TextureManager {

public:
	static	SDL_Texture* LoadTexture(const char* fileName);
	static	void Draw(SDL_Texturer* tex, SDL_Rect sourcePosisiton, SDL_Rect destinationPosisiton);

};

