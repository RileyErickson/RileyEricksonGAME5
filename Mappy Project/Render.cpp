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
Render::~Render() {
	al_destroy_sample(moo);
	al_destroy_sample(collisionSound);
	al_destroy_font(F);
	al_destroy_font(StartTXT);
	al_destroy_font(Timer);
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
			//erases the hit cow
			cows.erase(cows.begin() + loc);
			//updates the score and gives the player 1 extra second per cow hit.
			score++;
			Gscore++;
			time++;
			//if there was a hit we add the marker for it
			markers.push_back(Marker(mouse_x, mouse_y));
			//plays sound if collision with ship
			if(Coll)
				al_play_sample(collisionSound, 0.9, 0.0, 0.8, ALLEGRO_PLAYMODE_ONCE, NULL);
			
			//if a goal is completed then we want to increase the goal for the next round and then give
			//the player their bonus time.
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
//draws the start Screen
al_draw_filled_rectangle(0 , 0 , 800 , 900, al_map_rgb(50, 100, 100));
al_draw_textf(Timer, al_map_rgb(200, 20, 20), 400, 200, ALLEGRO_ALIGN_CENTER, "COW SHOOTER");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "SHOOT COWS TO GAIN MORE TIME");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "WASD TO MOVE / MOUSE TO FIRE");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 500, ALLEGRO_ALIGN_CENTER, "COMPLETING A EXTERMIATION GOAL");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 600, ALLEGRO_ALIGN_CENTER, "GETS YOU 5 EXTRA SECONDS");
al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400, 700, ALLEGRO_ALIGN_CENTER, "CLICK ANYWHERE TO START");
al_flip_display();
//waits till the user clicks to the screen
while (true) {
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		break;
	}
}
//resets time to ensure its update before the gameplay begins
time = 30 + al_get_time();
}
void Render::renderScore(int view_x, int view_y) {
	//renders the score board on the bottom of the screen
	al_draw_filled_rectangle(0 + view_x, 800 + view_y, 800 + view_x, 900 + view_y, al_map_rgb(50, 50, 50));
	al_draw_textf(Timer, al_map_rgb(255, 40, 40), 400 + view_x, 820 +view_y, ALLEGRO_ALIGN_CENTER, "%d", static_cast<int>(time- al_get_time()) );
	al_draw_textf(F, al_map_rgb(255, 255, 255), 5 + view_x, 840 + view_y, ALLEGRO_ALIGN_LEFT, "Bonus: %d/%d",Gscore, goal);
	al_draw_textf(F, al_map_rgb(55, 255, 55), 735 + view_x, 840 + view_y, ALLEGRO_ALIGN_RIGHT, "Score %d", score);


}
//renders the score on the bottem of the screen
void Render::renderEnd(int view_x,int view_y) {
	al_draw_filled_rectangle(0+ view_x, 0+ view_y, 800+ view_x, 900+ view_y, al_map_rgb(50, 50, 50));
	al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400 + view_x, 300 + view_y, ALLEGRO_ALIGN_CENTER, "CONGRATS YOU SHOT ");
	al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400 + view_x, 400 + view_y, ALLEGRO_ALIGN_CENTER, "%d COWS!", score);
	al_draw_textf(StartTXT, al_map_rgb(255, 255, 255), 400 + view_x, 500 + view_y, ALLEGRO_ALIGN_CENTER, "AND COMPLETED %d CHALLENGES", (goal/5)-1);
	al_flip_display();
	al_rest(7);

}
void Render::renderAim(int view_x, int view_y) {
	al_get_mouse_state(&mouse_state);
	al_draw_line(mouse_state.x + view_x-12, mouse_state.y + view_y, mouse_state.x + view_x+12, mouse_state.y + view_y, al_map_rgb(200, 50, 50), 3);
	al_draw_line(mouse_state.x + view_x, mouse_state.y + view_y - 12, mouse_state.x + view_x, mouse_state.y + view_y + 12, al_map_rgb(200, 50, 50), 3);
	al_draw_circle(mouse_state.x + view_x, mouse_state.y + view_y,12, al_map_rgb(200, 50, 50), 3);
}