#pragma once
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
};

