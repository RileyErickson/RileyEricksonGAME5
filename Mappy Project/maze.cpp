#include "maze.h"
#include <iostream>
#include <cstdio> 
maze::maze(int level)
{
	//loads the level needed 
	switch (level) {
	case(1):MapLoad("level1.fmp", 1);break;
	case(2):MapLoad("level2.fmp", 1); break;
	case(3):MapLoad("level3.fmp", 1); break;
		}
}
maze::~maze()
{

}
//draws the maze
void maze::drawMaze() {
	MapDrawBG(0, 0, 0, 0, 1248 - 1, 768 - 1);
	MapDrawFG(0, 0, 0, 0, 1248 - 1, 768 - 1, 0);
}
bool maze::getWall(int x, int y) {
	//checks if  any of the 4 corners of the character are in a wall
	// x and y are the cords of the character
	//top left
	blockdata = MapGetBlock((x+15) / mapblockwidth,(y+15) / mapblockwidth);
	if (blockdata->tl) {
		return true;
	}
	//TR
	blockdata = MapGetBlock((x + 80 )/ mapblockwidth,(y + 15)/ mapblockwidth);
	if (blockdata->tl) {
		return true;
	}
	//BL
	blockdata = MapGetBlock((x + 15)/ mapblockwidth,(y + 80)/ mapblockwidth);
	if (blockdata->tl) {
		return true;
	}
	//BR
	blockdata = MapGetBlock((x+80)/ mapblockwidth, (y+80)/ mapblockwidth);
	if (blockdata->tl) {
		return true;
	}
	return false;
}
