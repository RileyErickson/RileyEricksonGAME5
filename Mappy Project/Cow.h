#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Cow
{
public:
	Cow();
	void move();
	bool IsLocation(int x, int y);
private:
	int x1;
	int y1;
	int y2;
	int x2;
	int PosX;
	int PosY;
	bool up;
	double MovePercent;
	double Distance;
	double lastFrame;
	int curFrame;
	int flag;
    ALLEGRO_BITMAP* CSheet;
	ALLEGRO_BITMAP* frame;
};

