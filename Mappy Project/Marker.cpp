#include "Marker.h"
	Marker::Marker(int Cx, int Cy) {
		 x = Cx;
		 y = Cy;
		time = al_get_time();
		Marker1 = al_load_bitmap("markerClouds.png");
		Marker2 = al_load_bitmap("marker2.png");
	}
	void Marker::render() {
		//loads the correct spot we only want the clouds for a split second
		if (time + .2 > al_get_time()) 
			al_draw_bitmap(Marker1,x- 96/2, y - 96 / 2,0);
		else 
			al_draw_bitmap(Marker2, x - 96 / 2, y - 96 / 2, 0);
	}

