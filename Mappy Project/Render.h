#pragma once
#include "Cow.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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
	private:
		int score;
		double time;
		std::vector<Cow> cows;
		ALLEGRO_TRANSFORM camera;
		int CowSpawn;




};

