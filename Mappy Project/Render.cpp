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
	//test UFO/LAZER
	al_draw_filled_circle(400 + view_x, 400 + +view_y, 3, al_map_rgb(200, 0, 0));
	al_draw_line(400 + view_x, 400 + view_y, mouse_x + view_x, mouse_y + view_y, al_map_rgb(200, 0, 0), 3);
}
void Render::RenderCows(int mouse_x, int mouse_y) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, cows.size());
	int loc = 0;
	if (al_get_time() > CowSpawn + 1) {
		if (dis(gen) <= 5) { cows.push_back(Cow()); }
		CowSpawn = al_get_time();
	}
	for (Cow& C : cows) {
		C.move();
	}
	for (Cow& C : cows) {
		if (C.IsLocation(mouse_x, mouse_y)) {
			std::cout << loc << " length" << cows.size()<< std::endl;
			cows.erase(cows.begin() + loc);
			break;
		}
		loc++;
	}
	
}