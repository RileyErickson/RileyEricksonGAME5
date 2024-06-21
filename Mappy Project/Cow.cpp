#include "Cow.h"
#include <random>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>

Cow::Cow() {
	CSheet = al_load_bitmap("CowSprites.png");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(100, 2700);
	//the two ends of the line the cow will move in
	//longer the line the faster the cow will move
	x1 = dis(gen);
	y1 = dis(gen);
	x2 = dis(gen);
	y2 = dis(gen);
	//position of the cow
	PosX = x1;
	PosY = y1;
	//used for moving the cow up and down its line
	MovePercent = 0.001;
	Distance = 0;
	//which way to render the cow 
	up = true;
	curFrame = 0;
	flag = 0;
	lastFrame = al_get_time();
}

void Cow::move() {
	//handles finding the position along the line
		PosX = x1 + Distance * (x2 - x1);
		PosY = y1 + Distance * (y2 - y1);
		if (up) {
			Distance += MovePercent;
			if (Distance >= 1.0) 
				up = false;
		}
		else if (!up) {
			Distance -= MovePercent;
			if (Distance <= 0.0)
				up = true;	
	
		}
		//slows down the animation
		if (al_get_time() > lastFrame + 0.2) {
			curFrame++;
			lastFrame = al_get_time();
		}
	if (curFrame > 8) {
		curFrame = 1;
	}
	int fx = 0;
	int fy = 0;
	for (int i = 0; i < curFrame % 4; i++)
		fx += 96;
	if (curFrame >= 4)
		fy += 96;

	if (!up) {flag = ALLEGRO_FLIP_VERTICAL; }
	else { flag = 0; }
	frame = al_create_sub_bitmap(CSheet, fx, fy, 96, 96);
	
	al_draw_rotated_bitmap(frame, 96 / 2, 96 / 2, PosX,PosY, atan2(y2 - y1, x2 - x1) + 1.57, flag);
	

}
//returns true if the provide location is inside the cow
bool Cow::IsLocation(int x, int y) {
	if (( 90 > abs(x - (PosX+(96/2))))&& (90 > abs(y - (PosY + (96 / 2))))) 
		return true;
	
	return false;
}