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
    bool keys[] = { false, false, false, false };
    enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    int width = 1248;
    int height = 768;
    ALLEGRO_DISPLAY* display = al_create_display(width, height); 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    maze m(1);
    Character WizardRat;
    WizardRat.InitChar(10, 3 * 92);
    al_start_timer(timer);
    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
         if ((keys[UP])&&!(m.getWall(WizardRat.getX(), WizardRat.getY() - 3)))
            WizardRat.UpdateChar(0, -3, 2);
         if ((keys[DOWN]) && !(m.getWall(WizardRat.getX(), WizardRat.getY() + 3)))
            WizardRat.UpdateChar(0, 3, 2);
         if ((keys[LEFT]) &&!(m.getWall(WizardRat.getX()-3, WizardRat.getY()))&&!(WizardRat.getX()-3 <= 0))
            WizardRat.UpdateChar(-3, 0, 1);
         if ((keys[RIGHT])&& !(m.getWall(WizardRat.getX() + 3, WizardRat.getY())) && !(WizardRat.getX() +3 >= 1248))
            WizardRat.UpdateChar(3, 0, 0);

        if (ev.type == ALLEGRO_EVENT_TIMER){
        }
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
        m.drawMaze();
        WizardRat.DrawChar();
        
        if (m.getWall(WizardRat.getX(), WizardRat.getY())) {
            std::cout << "HIT" << std::endl;

        }
        //test
        //test
        //test
        //test
        //
        if (true) {
            //TL
            al_draw_filled_circle(WizardRat.getX()+15, WizardRat.getY()+15, 5, al_map_rgb(255, 0, 0));
            //TR
            al_draw_filled_circle(WizardRat.getX() + 80, WizardRat.getY() + 15, 5, al_map_rgb(255, 0, 0));
            //BL
            al_draw_filled_circle(WizardRat.getX() + 15, WizardRat.getY() + 80, 5, al_map_rgb(255, 0, 0));
            //BR
            al_draw_filled_circle(WizardRat.getX() + 80, WizardRat.getY() + 80, 5, al_map_rgb(255, 0, 0));

        }
        al_flip_display();

    }
}
