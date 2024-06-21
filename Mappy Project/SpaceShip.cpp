#include "SpaceShip.h"
SpaceShip::SpaceShip() {
	UFO = al_load_bitmap("spaceship.png");
	rotate = 0;
	scale = 1;
	ScaleDir = true;
}
SpaceShip::~SpaceShip() {
	al_destroy_bitmap(UFO);
}
void SpaceShip::render(int view_x, int view_y) {
	if(ScaleDir) {
		scale += 0.05/4;
		if (scale >= 1.2)
			ScaleDir = false;
	}
	else if (!ScaleDir) {
		scale -= 0.05/4;
		if (scale <= 1)
			ScaleDir = true;

	}
	rotate += 0.017 / 3;
	al_draw_scaled_rotated_bitmap(UFO, 96 / 2, 96 / 2, 400 + view_x, 400 + view_y, scale, scale, rotate, 0);
}