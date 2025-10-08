#pragma once
#include <string>

class Map {
public:
	Map();
	~Map();

 	void loadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX,int srcY, int xpos, int ypos);

private:
	
};
