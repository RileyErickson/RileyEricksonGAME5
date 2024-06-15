#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Character.h"
#include "mappy_A5.h"
#include <iostream>
#include "maze.h"

using namespace std;
int main()
{
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    int width = 1248;
    int height = 768;
    ALLEGRO_DISPLAY* display = al_create_display(width, height); 
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer;
    Character Rat;
     if (MapLoad("level1.fmp", 1))
        return -5;
    Rat.InitChar(100, 0);
    while (true) {        
        MapDrawBG(0, 0, 0, 0, width-1, height-1);
        MapDrawFG(0, 0, 0, 0, width - 1, height - 1, 0);
        al_rest(0.1);
        al_flip_display();

    }
}