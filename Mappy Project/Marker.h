#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Marker
{
	public:
		Marker(int Cx, int Cy);
		void render();
	private:
		int x;
		int y;
		double time;
		ALLEGRO_BITMAP* Marker1;
		ALLEGRO_BITMAP* Marker2;


};

