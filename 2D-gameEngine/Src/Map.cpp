#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;


Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts){
	scaledSize = ms * ts;
}

Map::~Map() {
}

void Map::loadMap(std::string path, int sizeX, int sizeY){
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;
	
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();
	
	for(int y = 0; y < sizeY; y++){
		for(int x = 0; x < sizeX; x++){
			mapFile.get(c);

			//Check collider type 1 full, 2 bottom half, 3 top half, 4 left half, 5 right half
			if(c != '0'){

				//optional, change tag for each different type, update ColliderComponent
				switch (c){
					case 1:
						auto& tcol(manager.addEntity());
						tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize, c);
						tcol.addGroup(Game::groupColliders);
						break;
					case 2:
						auto& tcol(manager.addEntity());
						tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize, c);
						tcol.addGroup(Game::groupColliders);
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						break;
					//May not need these, full tile may be a better option
					//Bottom left
					case 14:
						//create 2 collider components, one type 1 and one type 4
						break;
					//Bottom right
					case 15:
						break;
					//Top left
					case 24:
						break;
					//Top right
					case 25:
						break;
					default:
						break;
						
				}
				/*auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);*/
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX,int srcY, int xpos, int ypos){
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos,tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
}
