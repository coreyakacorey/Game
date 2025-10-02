#include "Game.h"

class Map {
public:
  Map();
  ~Map();

  void loadMap();
  void drawMap();

private:
  SDL_Rect sourceRectangle, destinationRectangle;

  SDL_Texture* dirt;
  SDL_Textuer* grass;
  SDL_Texture* water;

  int map[20][25];

}
