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
void maze::drawMaze() {
	MapDrawBG( 0, 0, 0, 0, 2880 -1, 2880 - 1);
}

