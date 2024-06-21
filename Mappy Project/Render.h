#pragma once
#include "Cow.h"
#include "Marker.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "mappy_A5.h"
#include <iostream>
#include <random>
class Render
{
	public:
		Render();
		void RenderStart(ALLEGRO_EVENT_QUEUE* event_queue);
		void RenderFarmUFO(int view_x, int view_y,int mouse_x,int mouse_y);
		void RenderCows(int mouse_x, int mouse_y, bool C);
		double getAllowedTime() { return time; };
		void renderScore(int view_x, int view_y);
	private:
		int score;
		int goal;
		double time;
		int Gscore;
		std::vector<Cow> cows;
		std::vector<Marker> markers;
		ALLEGRO_TRANSFORM camera;
		int CowSpawn;
		ALLEGRO_FONT* F;
		ALLEGRO_FONT* Timer;
		ALLEGRO_FONT* StartTXT;
		ALLEGRO_SAMPLE* moo;
		ALLEGRO_SAMPLE* collisionSound;




};

