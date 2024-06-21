#include "Cow.h"
#include <random>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
Cow::Cow() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(100, 2700);
	//the two ends of the line the cow will move in
	x1 = dis(gen);
	y1 = dis(gen);
	x2 = dis(gen);
	y2 = dis(gen);
	//position of the cow
	PosX = x1;
	PosY = y1;
	MovePercent = 0.001;
	Distance = 0;
	up = true;
}
void Cow::move() {
	 
	PosX = x1 + Distance * (x2 - x1);
	PosY = y1 + Distance * (y2 - y1);
	if (up) {
		Distance += MovePercent;
		if (Distance >= 1.0) {
			Distance = 1.0;
			up = false;
		}
	}
	else if(!up){
		Distance -= MovePercent;
		if (Distance <= 0.0) {
			Distance = 0.0;
			up = true;
		}
	}
	al_draw_filled_circle(PosX, PosY, 10, al_map_rgb(200, 10, 200));
	al_draw_line(x1, y1, x2, y2, al_map_rgb(200, 0, 0), 3);

}
bool Cow::IsLocation(int x, int y) {
	return true;
}