#include "Character.h"
using namespace std;
Character::Character()
{
	WizardRat = NULL;
	needToDraw = true;

}
Character::~Character()
{
	al_destroy_bitmap(WizardRat);
}
void Character::InitChar(int Sx, int Sy)
{
	//starting x and y
	x = Sx;
	y = Sy;

	curFrame = 0;
	frameCount = 0;
	frameWidth = 32 * 6; //frames are 32/32 big, but to prevent pixelazition when exporting they
	frameHeight = 32 * 6;// are exported 6 times larger then needed

	//spritemap for the main character
	WizardRat = al_load_bitmap("RatSheet.png");
}


void Character::UpdateChar(int Mx, int mY, int flip) {
	curFrame++;
	if (curFrame >= 10) {
		curFrame = 0;
	}
	x += Mx;
	y += mY;
	//only valid flags are 0 and 1
	if (!((flip > 1) || (flip < 0))) {
		flags = flip;
	}
	needToDraw = true;
}
void Character::DrawChar()
{
	int fx = 0;
	int fy = 0;
	for (int i = 0; i < curFrame % 5; i++)
		fx += frameWidth;
	if (curFrame >= 5)
		fy += frameHeight;

	al_draw_scaled_bitmap(WizardRat, fx, fy, frameWidth, frameHeight, x, y, 98, 98, flags);
	al_flip_display();
	needToDraw = false;

}
int Character::getX() {
	return x;
}
int Character::getY() {
	return y;
}