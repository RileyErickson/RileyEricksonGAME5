#include "Character.h"
using namespace std;
Character::Character()
{
	WizardRat = al_load_bitmap("RatSheet.png");;
	needToDraw = true;
	counter = 0;
}
Character::~Character()
{
	al_destroy_bitmap(WizardRat);
}
//loads the character and data for the sprite map
void Character::InitChar(int Sx, int Sy)
{
	//starting x and y
	x = Sx;
	y = Sy;

	curFrame = 0;
	frameCount = 0;
	frameWidth = 32 * 6; //frames are 32/32 big, but for scaling they are
	frameHeight = 32 * 6;// are exported 6 times larger then they were made
}


void Character::UpdateChar(int Mx, int mY, int flip) {
	//counter slows down the walking cycle so it looks better
	if (counter <= 4) {
		counter++;
	}
	else {
		//once the counter triggers we reset it and move to the next frame
		curFrame++;
		counter = 0;
	}
	if (curFrame >= 10) {
		curFrame = 0;
	}
	//take x and y movement and add it to the cords
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
	//position of frame in sprite map
	int fx = 0;
	int fy = 0;
	//converts current frame to a position in the sprite map
	for (int i = 0; i < curFrame % 5; i++)
		fx += frameWidth;
	if (curFrame >= 5)
		fy += frameHeight;

	al_draw_scaled_bitmap(WizardRat, fx, fy, frameWidth, frameHeight, 400, 400, 100, 100, flags);
	needToDraw = false;

}
int Character::getX() {
	return x;
}
int Character::getY() {
	return y;
}
