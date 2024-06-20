#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Character.h"
#include "mappy_A5.h"
#include <iostream>
#include "maze.h"

using namespace std;
int main()
{
    int level = 1;
    bool done = false;
    bool keys[] = { false, false, false, false };
    enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    int width = 800;
    int height = 800;
    ALLEGRO_DISPLAY* display = al_create_display(width, height); 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_FONT* W = al_load_font("Starjedi.ttf", 40, 20);

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    maze* m = new maze(level);
    Character SpaceShip;
    //places main character at starting position
    SpaceShip.InitChar(1000-(96 / 2), 1000-(96/2));
    al_start_timer(timer);
    //main game loop
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        //checks if key has been pressed and if there is a wall in the wall
        //2 means dont flip character 1 means face left o means face right
        //corrasponds to allegro flags;
         if ((keys[UP])&&(SpaceShip.getY() - 406 > 15))
            SpaceShip.UpdateChar(0, -6, 2);
         if ((keys[DOWN]) && (SpaceShip.getY() - 394 < 2070))
            SpaceShip.UpdateChar(0, 6, 2);
         if ((keys[LEFT]) &&(SpaceShip.getX() - 406 > 15))
            SpaceShip.UpdateChar(-6, 0, 1);
         if ((keys[RIGHT])&& (SpaceShip.getX() - 394 < 2070))
            SpaceShip.UpdateChar(6, 0, 0);

        if (ev.type == ALLEGRO_EVENT_TIMER){
        }
        //handles movement
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            }
        }
        if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            }
        }
        //exit conditions if they run out of time or complte all 4 levels

        //draws the screen
        std::cout << SpaceShip.getX() -400 << "y" <<  SpaceShip.getY() - 400 << std::endl;
        m->drawMaze(SpaceShip.getX() - 400, SpaceShip.getY() - 400);
        SpaceShip.DrawChar();
        al_draw_filled_rectangle(96 * 12, 0, 96 * 13, 96, al_map_rgb(0, 0, 0));
        al_draw_textf(W, al_map_rgb(200, 50, 50), (96 * 12)+ 49, 19, ALLEGRO_ALIGN_CENTER, "%d", static_cast<int>(60.0 - al_get_time()));
      
        al_flip_display();

    }
    al_destroy_display(display);
}
