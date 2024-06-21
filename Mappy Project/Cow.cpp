#include "Cow.h"
#include <random>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>

Cow::Cow() {
	CSheet = al_load_bitmap("CowSheet.png");
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
	curFrame = 0;
	flag = 0;
}
void Cow::move() {
	//handles finding the position along the line
		PosX = x1 + Distance * (x2 - x1);
		PosY = y1 + Distance * (y2 - y1);
		if (up) {
			Distance += MovePercent;
			if (Distance >= 1.0) {
				Distance = 1.0;
				up = false;
			}
		}
		else if (!up) {
			Distance -= MovePercent;
			if (Distance <= 0.0) {
				Distance = 0.0;
				up = true;	
			}
		}
		//handles finding the cow
		curFrame++;
	if (curFrame >= 10) {
		curFrame = 0;
	}
	int fx = 0;
	int fy = 0;
	for (int i = 0; i < curFrame % 5; i++)
		fx += 96;
	if (curFrame >= 5)
		fy += 96;

	if (up) {flag = ALLEGRO_FLIP_VERTICAL; }
	else { flag = 0; }
	al_draw_filled_circle(PosX, PosY, 10, al_map_rgb(200, 10, 200));
	al_draw_line(x1, y1, x2, y2, al_map_rgb(200, 0, 0), 3);
	frame = al_create_sub_bitmap(CSheet, fx, fy, 96, 96);
	if(x2 > x1)
		al_draw_rotated_bitmap(frame, 96 / 2, 96 / 2, PosX,PosY, 90 -(x2 - x1), flag);
	else
		al_draw_rotated_bitmap(frame, 96 / 2, 96 / 2, PosX, PosY, 90 -(x1 - x2), flag);

}
bool Cow::IsLocation(int x, int y) {
	if ( 90 > abs(x - (PosX+(96/2)))) {
		if (90 > abs(y - (PosY + (96 / 2)))) {
			std::cout << "HIT" << std::endl;
			return true;
		}
	}
	std::cout << abs(y - (PosY + (96 / 2))) << std::endl;

	return true;
}