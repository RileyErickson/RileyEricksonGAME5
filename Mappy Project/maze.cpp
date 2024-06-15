#include "maze.h"
#include <iostream>
#include <cstdio> 
maze::maze(int level)
{
	char mp[10];
	std::sprintf(mp, "level%d.fmp", level);
	if ((level > 5) && (level > 0))
		MapLoad("level5.fmp", 1);
	else
		MapLoad(mp, 1);

}
maze::~maze()
{

}
void maze::drawMaze() {
	MapDrawBG(0, 0, 0, 0, 1248 - 1, 768 - 1);
	MapDrawFG(0, 0, 0, 0, 1248 - 1, 768 - 1, 0);
}
bool maze::getWall(int x, int y) {
	return true;
}