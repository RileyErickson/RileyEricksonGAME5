#include "Marker.h"
	Marker::Marker(int Cx, int Cy) {
		 x = Cx;
		 y = Cy;
		time = al_get_time();
		Marker1 = al_load_bitmap("markerClouds.png");
		Marker2 = al_load_bitmap("marker2.png");
	}
	void Marker::render() {
		if (time + .2 > al_get_time()) 
			al_draw_bitmap(Marker1,x, y,0);
		else 
			al_draw_bitmap(Marker2, x, y, 0);
	}

