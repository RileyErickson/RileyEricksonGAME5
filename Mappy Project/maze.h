#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "maze.h"
#include "mappy_A5.h"
class maze
{
private:
	int location;
	int charX;
	int charY;
	BLKSTR* blockdata;
public:
	maze(int level);
	~maze();
	void drawMaze(int x, int y, int Vx, int Vy);
	bool getWall(int x, int y);

};

