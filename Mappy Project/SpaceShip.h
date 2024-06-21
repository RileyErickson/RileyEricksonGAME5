#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class SpaceShip
{
public:
	SpaceShip();
	void render(int view_x, int view_y);
private:
	double rotate;
	double scale;
	bool ScaleDir;
	ALLEGRO_BITMAP* UFO;
};

