#include "Render.h"
Render::Render() {
	//Alien Mushrooms by HAWTPIXEL - Darrell Flood 
	//https://www.fontspace.com/hawtpixel-darrell-flood
	F = al_load_font("AlienMushrooms.ttf", 60, 0);
	Timer = al_load_font("AlienMushrooms.ttf", 100, 0);
	MapLoad("farm.fmp", 1);
	CowSpawn = 0;
	goal = 5;
	Gscore = 0;
	time = 30 + al_get_time();
	score = 0;
}
void Render::RenderFarmUFO(int view_x, int view_y, int mouse_x, int mouse_y) {
	//handles scrolling the screen
	al_identity_transform(&camera);
	al_translate_transform(&camera, -view_x, -view_y);
	al_use_transform(&camera);
	//draws the farm
	MapDrawBG(0, 0, 0, 0, 2880 - 1, 2880 - 1);
	//test UFO/LAZER UFO will be replaced with real class later just a reference point for rn
	al_draw_filled_circle(400 + view_x, 400 + +view_y, 3, al_map_rgb(200, 0, 0));
	al_draw_line(400 + view_x, 400 + view_y, mouse_x + view_x, mouse_y + view_y, al_map_rgb(200, 0, 0), 3);
}
void Render::RenderCows(int mouse_x, int mouse_y) {
	std::random_device rd;
	std::mt19937 gen(rd());
	//generates a random cow the more cows there are the less likely a cow is to spawn
	std::uniform_int_distribution<> dis(0, cows.size());
	int loc = 0;
	if (al_get_time() > CowSpawn + 1) {
		if (dis(gen) <= 5) { cows.push_back(Cow()); }
		CowSpawn = al_get_time();
	}
	//updates all the cows locations
	for (Cow& C : cows)
		C.move();
	//checks if any cows have been ran over or shot.
	for (Cow& C : cows) {
		if (C.IsLocation(mouse_x, mouse_y)) {
			cows.erase(cows.begin() + loc);
			score++;
			Gscore++;
			time++;
			if (Gscore == goal) {
				Gscore = 0;
				goal += 5;
				time += 6;
			}
			std::cout << score << std::endl;
			break;
		}
		loc++;
	}
	
}
void Render::renderScore(int view_x, int view_y) {

	al_draw_filled_rectangle(0 + view_x, 800 + view_y, 800 + view_x, 900 + view_y, al_map_rgb(50, 50, 50));
	al_draw_textf(Timer, al_map_rgb(255, 40, 40), 400 + view_x, 820 +view_y, ALLEGRO_ALIGN_CENTER, "%d", static_cast<int>(time- al_get_time()) );
	al_draw_textf(F, al_map_rgb(255, 255, 255), 5 + view_x, 840 + view_y, ALLEGRO_ALIGN_LEFT, "Bonus: %d/%d",Gscore, goal);
	al_draw_textf(F, al_map_rgb(55, 255, 55), 735 + view_x, 840 + view_y, ALLEGRO_ALIGN_RIGHT, "Score %d", score);


}