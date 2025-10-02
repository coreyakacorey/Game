#include "Map.h"

int lvl1[20][25] = {
  {0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,2,2,1,1,2,2,2,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,2,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,2,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map(){
  dirt = TextureManager::LoadTexture("assets/drit.png");
  grass = TextureManager::LoadTexture("assets/grass.png");
  water = TextureManager::LoadTexture("assets/water.png");

  LoadMap(lvl1);

  source.x = source.y = 0;
  source.w = destination.w = 32;
  source.h = destination.h = 32;
  destination.x = destination.y = 0;
  
}

void Map::loadMap(int arr[20][25]){
  for(int row = 0; row < 20; row++){
    for(int column = 0; column < 25; column++){
      map[row][column] = arr[row][column];
    }
  }
}

void Map::drawMap(){
  int type = 0;
  
  for(int row = 0; row < 20; row++){
    for(int column = 0; column < 25; column++){
      type = map[row][column];
      
      destination.x = column * 32;
      destination.y = row * 32;
      
      switch(type){
        case 0:
          TextureManager::Draw(water, source, destination);
          break;
        case 1:
          TextureManager::Draw(grass, source, destination);
          break;
        case 2:
          TextureManager::Draw(dirt, source, destination);
          break;
        default:
          break;
      }
    }
  }
}
