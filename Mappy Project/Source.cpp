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
    maze* m = new maze(level);
    Character SpaceShip;
    //places main character at starting position
    SpaceShip.InitChar(view_x + 400, view_y+ 400);
    al_start_timer(timer);
    //main game loop
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        //checks if key has been pressed and if there is a wall in the wall
        //2 means dont flip character 1 means face left o means face right
        //corrasponds to allegro flags;
        if ((keys[UP])) {
            SpaceShip.UpdateChar(0, -6, 2);
            if (view_y - 6 > 15)
                view_y += -6;
        }
        if ((keys[DOWN])) {
            SpaceShip.UpdateChar(0, 6, 2);
            if (view_y + 6 < 2070)
                view_y += 6;
        }
        if ((keys[LEFT])) {
            SpaceShip.UpdateChar(-6, 0, 1);
            if(view_x -6 > 15)
                view_x += -6;
        }
        if ((keys[RIGHT])){
            SpaceShip.UpdateChar(6, 0, 0);
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
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
            displayBeam = al_get_time();
            std::cout << mouse_x << "\n y " << mouse_y << std::endl;
        }
        else if((displayBeam + 2) < al_get_time()) {
            mouse_x = 400;
            mouse_y = 400 ;
            std::cout <<"reset " << std::endl;

        }
       //handles scrolling the screen
        al_identity_transform(&camera);
        al_translate_transform(&camera, -view_x, -view_y);
        al_use_transform(&camera);


        m->drawMaze(SpaceShip.getX(), SpaceShip.getY(), view_x, view_y);
        //load space ship here later
        al_draw_filled_circle(400 + view_x , 400+ +view_y, 3, al_map_rgb(200, 0, 0));
        al_draw_line(400 + view_x, 400 + view_y, mouse_x + view_x, mouse_y + view_y, al_map_rgb(200, 0, 0), 3);
        //SpaceShip.DrawChar();
        al_draw_filled_rectangle(96 * 12, 0, 96 * 13, 96, al_map_rgb(0, 0, 0));
        al_draw_textf(W, al_map_rgb(200, 50, 50), (96 * 12)+ 49, 19, ALLEGRO_ALIGN_CENTER, "%d", static_cast<int>(60.0 - al_get_time()));
      
        al_flip_display();

    }
    al_destroy_display(display);
}
