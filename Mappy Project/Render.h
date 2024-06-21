#pragma once
#include "Cow.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "mappy_A5.h"
#include <iostream>
#include <random>
class Render
{
	public:
		Render();
		void RenderStart();
		void RenderFarmUFO(int view_x, int view_y,int mouse_x,int mouse_y);
		void RenderCows(int mouse_x, int mouse_y);
		double getAllowedTime() { return time; };
		void renderScore(int view_x, int view_y);
	private:
		int score;
		int goal;
		double time;
		int Gscore;
		std::vector<Cow> cows;
		ALLEGRO_TRANSFORM camera;
		int CowSpawn;
		ALLEGRO_FONT* F;
		ALLEGRO_FONT* Timer;




};

