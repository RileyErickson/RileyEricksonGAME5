#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Cow.h"
#include "mappy_A5.h"
#include <iostream>
#include "Render.h"
using namespace std;
int main()
{
    int level = 1;
    bool done = false;
    bool keys[] = { false, false, false, false };
    enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    int width = 800;
    int height = 800;
    int REAL_W = 2880;
    int REAL_H = 2880;
    float view_x = 500;
    float view_y = 500;
    int mouse_x = 400 + view_x;
    int mouse_y = 400 + view_x;
    double displayBeam = -10000;
    ALLEGRO_DISPLAY* display = al_create_display(width, height); 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_FONT* W = al_load_font("Starjedi.ttf", 40, 20);
    ALLEGRO_TRANSFORM camera;
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    //places main character at starting position
    al_start_timer(timer);
    //main game loop
    Render render;
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        //checks if key has been pressed and if there is a wall in the wall
        //2 means dont flip character 1 means face left o means face right
        //corrasponds to allegro flags;
        if ((keys[UP])) {
            if (view_y - 6 > 15)
                view_y += -6;
        }
        if ((keys[DOWN])) {
            if (view_y + 6 < 2070)
                view_y += 6;
        }
        if ((keys[LEFT])) {
            if(view_x -6 > 15)
                view_x += -6;
        }
        if ((keys[RIGHT])){
            if(view_x+ 6 < 2070)
                view_x += 6;
        }

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
        //renders lazer beam
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
            displayBeam = al_get_time();
        }
        else if((displayBeam + 0.2) < al_get_time()) {
            mouse_x = 400;
            mouse_y = 400 ;
        }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            render.RenderFarmUFO(view_x, view_y, mouse_x, mouse_y); \
            render.RenderCows(mouse_x+ +view_x, mouse_y+ view_y);

            al_flip_display();
        }
    }
    al_destroy_display(display);
}
