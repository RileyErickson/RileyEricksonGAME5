#include "Render.h"
Render::Render() {
	MapLoad("farm.fmp", 1);
	CowSpawn = 0;
}
void Render::RenderFarmUFO(int view_x, int view_y, int mouse_x, int mouse_y) {
	//handles scrolling the screen
	al_identity_transform(&camera);
	al_translate_transform(&camera, -view_x, -view_y);
	al_use_transform(&camera);
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
			std::cout << loc << " length" << cows.size()<< std::endl;
			cows.erase(cows.begin() + loc);
			break;
		}
		loc++;
	}
	
}