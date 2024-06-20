#include "maze.h"
#include <iostream>
#include <cstdio> 
maze::maze(int level)
{
	MapLoad("farm.fmp", 1);
}

maze::~maze()
{

}
//draws the maze
void maze::drawMaze(int x, int y, int View_x, int View_y) {
	MapDrawBG( 0, 0, 0, 0, 2880 -1, 2880 - 1);
	//MapDrawFG(x-200, y, 0, 0, 800 - 1, 800 - 1, 0);
}
bool maze::getWall(int x, int y) {
	return false;
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
