#include "Render.h"
Render::Render() {
	//Alien Mushrooms by HAWTPIXEL - Darrell Flood 
	//https://www.fontspace.com/hawtpixel-darrell-flood
	//Milky Cow by Wellscript Studio
	//https://www.fontspace.com/wellscript-studio
	F = al_load_font("AlienMushrooms.ttf", 60, 0);
	Timer = al_load_font("AlienMushrooms.ttf", 100, 0);
	StartTXT = al_load_font("CowText.otf", 50, 0);
	moo = al_load_sample("moo.mp3");
	collisionSound = al_load_sample("Collision.wav");
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
	for (Marker& M : markers)
		M.render();
	//test UFO/LAZER UFO will be replaced with real class later just a reference point for rn
	al_draw_line(400 + view_x, 400 + view_y, mouse_x + view_x, mouse_y + view_y, al_map_rgb(200, 0, 0), 3);
	ship.render(view_x, view_y);

}
void Render::RenderCows(int mouse_x, int mouse_y, bool Coll) {
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
			markers.push_back(Marker(mouse_x, mouse_y));
			//plays sound if collision with ship
			if(Coll){
				al_play_sample(collisionSound, 0.9, 0.0, 0.8, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			if (Gscore == goal) {
				Gscore = 0;
				goal += 5;
				time += 6;
			}
			al_play_sample(moo, 0.7, 0.0, 1.7, ALLEGRO_PLAYMODE_ONCE, NULL);
			break;
		}
		loc++;
	}
	
}
void Render::RenderStart(ALLEGRO_EVENT_QUEUE* event_queue) {
ALLEGRO_EVENT ev;
al_draw_filled_rectangle(0 , 0 , 800 , 900, al_map_rgb(50, 100, 100));
al_draw_textf(Timer, al_map_rgb(200, 20, 20), 400, 200, ALLEGRO_ALIGN_CENTER, "COW SHOOTER");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "SHOOT COWS TO GAIN MORE TIME");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "WASD TO MOVE / MOUSE TO FIRE");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "COMPLETING A EXTERMIATION GOAL");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "GETS YOU 5 EXTRA SECONDS");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 700, ALLEGRO_ALIGN_CENTER, "CLICK ANYWHERE TO START");
al_flip_display();
while (true) {
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		break;
	}
}
time = 30 + al_get_time();
}
void Render::renderScore(int view_x, int view_y) {

	al_draw_filled_rectangle(0 + view_x, 800 + view_y, 800 + view_x, 900 + view_y, al_map_rgb(50, 50, 50));
	al_draw_textf(Timer, al_map_rgb(255, 40, 40), 400 + view_x, 820 +view_y, ALLEGRO_ALIGN_CENTER, "%d", static_cast<int>(time- al_get_time()) );
	al_draw_textf(F, al_map_rgb(255, 255, 255), 5 + view_x, 840 + view_y, ALLEGRO_ALIGN_LEFT, "Bonus: %d/%d",Gscore, goal);
	al_draw_textf(F, al_map_rgb(55, 255, 55), 735 + view_x, 840 + view_y, ALLEGRO_ALIGN_RIGHT, "Score %d", score);


}