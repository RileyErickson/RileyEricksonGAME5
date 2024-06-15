#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;
class Character
{
public:
	Character();
	~Character();
	void InitChar(int width, int height);
	void UpdateChar(int Mx, int mY, int flip);
	void DrawChar();
	int getY();
	int getX();
private:

	float x;
	float y;
	bool needToDraw;
	int curFrame;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int flags;

	ALLEGRO_BITMAP* WizardRat;
};