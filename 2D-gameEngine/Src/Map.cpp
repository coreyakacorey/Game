#include "Map.h"
#include "TextureManager.h"

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
   
  dirt = TextureManager::LoadTexture("assests/dirt.png");
  grass = TextureManager::LoadTexture("assests/grass.png");
  water = TextureManager::LoadTexture("assests/water.png");

  loadMap(lvl1);

  sourceRectangle.x = sourceRectangle.y = 0;
  sourceRectangle.w = destinationRectangle.w = 32;
  sourceRectangle.h = destinationRectangle.h = 32;
  destinationRectangle.x = destinationRectangle.y = 0;
  
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
      //std::cout << type << std::endl;
      
      destinationRectangle.x = column * 32;
      destinationRectangle.y = row * 32;
      
      switch(type){
        case 0:
          TextureManager::Draw(water, sourceRectangle, destinationRectangle);
          //std::cout << "HERE" << std::endl;
          break;
        case 1:
          TextureManager::Draw(grass, sourceRectangle, destinationRectangle);
          break;
        case 2:
          TextureManager::Draw(dirt, sourceRectangle, destinationRectangle);
          break;
        default:
          break;
      }
    }
  }
}
