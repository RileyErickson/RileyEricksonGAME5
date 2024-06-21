#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Cow.h"
#include "mappy_A5.h"
#include <iostream>
#include "Render.h"
using namespace std;
bool keys[] = { false, false, false, false };
const enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
void Movement(ALLEGRO_EVENT ev);
int main()
{
    int level = 1;
    bool done = false;
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    int width = 800;
    int height = 800;
    int REAL_W = 2880;
    int REAL_H = 2880;
    float view_x = 500;
    float view_y = 500;
    int mouse_x = 400 + view_x;
    int mouse_y = 400 + view_x;
    double displayBeam = -1;
    bool Collison = true;
    //+ 100 added for rendering score area
    ALLEGRO_DISPLAY* display = al_create_display(width, height +100); 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);

  
    //sound effect made with https://sfxr.me/
    //background song made with music lab
    al_reserve_samples(4);
    ALLEGRO_SAMPLE* LazerEffect = al_load_sample("explosion.mp3");
    ALLEGRO_SAMPLE* BackGround = al_load_sample("background.wav");
    al_play_sample(BackGround, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    //main game loop
    Render render;
    al_register_event_source(event_queue, al_get_mouse_event_source());
 
    render.RenderStart(event_queue);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        //checks for movement and then sees if that movement would move past the edge of the screen
        if ((keys[UP])&& (view_y - 6 > 15))
            view_y += -6;
        if ((keys[DOWN])&& (view_y + 6 < 2070)) 
             view_y += 6;
        if ((keys[LEFT])&& (view_x - 6 > 15)) 
             view_x += -6;
        if ((keys[RIGHT])&&(view_x + 6 < 2070))
            view_x += 6;

        //handles taking user movement input
        Movement(ev);
        //records lazer beam location/plays sound effect
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
            al_play_sample(LazerEffect, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            displayBeam = al_get_time();
            Collison = false;
        }
        //handles how long to show lazer beam and resets the lazer if its been long enough
        else if((displayBeam + 0.2) < al_get_time()) {
            mouse_x = 400;
            mouse_y = 400 ;
            Collison = true;
        }
        //renders all the display objects
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            render.RenderFarmUFO(view_x, view_y, mouse_x, mouse_y); \
            render.RenderCows(mouse_x +view_x, mouse_y+ view_y,Collison);
            render.renderScore(view_x, view_y);
            al_flip_display();
        }
        if (render.getAllowedTime() - al_get_time() <= 0) {
            done = true;
        }
    }
    al_destroy_display(display);
}
void Movement(ALLEGRO_EVENT ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_W:
            keys[UP] = true;
            break;
        case ALLEGRO_KEY_S:
            keys[DOWN] = true;
            break;
        case ALLEGRO_KEY_A:
            keys[LEFT] = true;
            break;
        case ALLEGRO_KEY_D:
            keys[RIGHT] = true;
            break;
        }
    }
    if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        switch (ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            keys[UP] = false;
            break;
        case ALLEGRO_KEY_S:
            keys[DOWN] = false;
            break;
        case ALLEGRO_KEY_A:
            keys[LEFT] = false;
            break;
        case ALLEGRO_KEY_D:
            keys[RIGHT] = false;
            break;
        }
    }
}