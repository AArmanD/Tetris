#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int main()
{
    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(650, 800);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 510, 20, 0, "Next:");
            //al_draw_rectangle(0, 0, 500, 800, al_map_rgb(255, 255, 255), 3);

            //for (int i = 0; i < 500; i+= 50) {
            //    for (int j = 0; j < 800; j += 50) {
            //        al_draw_filled_rectangle((double)i, (double)j, (double)i + 50, (double)j + 50, al_map_rgb(0, 0, 255));
            //    }
            //}
            al_draw_filled_rectangle(0, 0, 50, 50, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(50, 0, 100, 50, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(100, 0, 150, 50, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(50, 50, 100, 100, al_map_rgb(0, 0, 255));
            al_draw_line(500, 0, 500, 800, al_map_rgb(255,255,255), 3);
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}