#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>

const int itetrimonio[2][16] = { {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}, {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0} };
const int ltetrimonio[4][9] = { {1,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,1,0},{0,0,0,1,1,1,0,0,1},{0,1,0,0,1,0,1,1,0} };
const int qtetrimonio[1][4] = { 1,1,1,1 };
const int ttetrimonio[4][9] = { {0,0,0,0,1,0,1,1,1},{1,0,0,1,1,0,1,0,0},{1,1,1,0,1,0,0,0,0},{0,0,1,0,1,1,0,0,1} };
const int ztetrimonio[2][9] = { {0,1,1,1,1,0,0,0,0},{0,1,0,0,1,1,0,0,1} };

//struct to determine where a tetrimonio of a distinct type is and which color it has
struct tetrimonio {
    int x;
    int y;
    int type;
    int heading;
    int color;
};

struct tetrimonio create_tetrimonio(){
    int number = rand() % 5;
    struct tetrimonio tet;

    switch (number)
    {
    case 0:
        tet.type = 0;
        tet.x = 3;
        tet.y = 0;
        tet.heading = 0;
        break;
    case 1:
        tet.type = 1;
        tet.x = 3;
        tet.y = 0;
        tet.heading = 0;
        break;
    case 2:
        tet.type = 2;
        tet.x = 4;
        tet.y = 0;
        tet.heading = 0;
        break;
    case 3:
        tet.type = 3;
        tet.x = 3;
        tet.y = 0;
        tet.heading = 0;
        break;
    case 4:
        tet.type = 4;
        tet.x = 3;
        tet.y = 0;
        tet.heading = 0;
        break;
    }

    return tet;
}

//this function draws a tetrimonio on the Gameboard
void draw_tetrimonio(int GameBoard[16][10], struct tetrimonio tet) {
    int count = 0;
    for (int i = tet.y; i < getTetrimonioWidth(tet.type) + tet.y; i++) {
        for (int j = tet.x; j < getTetrimonioWidth(tet.type) + tet.x; j++)
        {
            switch (tet.type)
            {
            case 0:
                GameBoard[i][j] = itetrimonio[tet.heading][count];
                break;
            case 1:
                GameBoard[i][j] = ltetrimonio[tet.heading][count];
                break;
            case 2:
                GameBoard[i][j] = qtetrimonio[tet.heading][count];
                break;
            case 3:
                GameBoard[i][j] = ttetrimonio[tet.heading][count];
                break;
            case 4:
                GameBoard[i][j] = ztetrimonio[tet.heading][count];
                break;
            }
            count++;
        }
    }
}

//this function deletes a tetrimonio out of the gameboard
void delete_tetrimonio(int GameBoard[16][10], struct tetrimonio tet) {
    for (int i = tet.y; i < getTetrimonioWidth(tet.type) + tet.y; i++) {
        for (int j = tet.x; j < getTetrimonioWidth(tet.type) + tet.x; j++)
        {
            GameBoard[i][j] = 0;
        }
    }
}

//this function checks whether a rotation is possible and returns 1 when possible 0 when not
int check_rotate_tetrimonio(int GameBoard[16][10], struct tetrimonio tet) {
    int rotatable = 1;
    if(tet.y + getTetrimonioWidth(tet.type) < 16)
    for (int i = tet.y; i < getTetrimonioWidth(tet.type) + tet.y; i++) {
        for (int j = tet.x; j < getTetrimonioWidth(tet.type) + tet.x; j++)
        {
            if (GameBoard[i][j] == 2) {
                return 0;
            }
        }
    }
    else {
        return 0;
    }

    return 1;
}

//this function rotates a tetrimonio
void rotate_tetrimonio(int GameBoard[16][10], struct tetrimonio* tet) {
    if (check_rotate_tetrimonio(GameBoard, *tet)) {
        switch (tet->type)
        {
        case 0:
            if (tet->heading == 0)
            {
                tet->heading = 1;
            }
            else {
                tet->heading = 0;
            } break;
        case 1:
            if (tet->heading < 3)
            {
                tet->heading++;
            }
            else {
                tet->heading = 0;
            } break;
        case 2: break;
        case 3:
            if (tet->heading < 3)
            {
                tet->heading++;
            }
            else {
                tet->heading = 0;
            } break;
        case 4:
            if (tet->heading == 0)
            {
                tet->heading = 1;
            }
            else {
                tet->heading = 0;
            } break;
        }
        delete_tetrimonio(GameBoard, *tet);
        draw_tetrimonio(GameBoard, *tet);
    }

    return;
}

//this function moves a tetrimonio down
int move_tetrimonio(int GameBoard[16][10], struct tetrimonio* tet) {
    int movableBlock = 0;
    int movable = 1;
    if (tet->y + getTetrimonioWidth(tet->type) < 16)
    {
        movableBlock = 1;
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) {
            if (GameBoard[i][j] == 1 && GameBoard[i + 1][j] == 2 //genau anschauen
                || GameBoard[i + 1][j] == 1 && i+1 == 15) {
                movable = 0;
            }
        }
    }

    if (movable) {
        for (int i = 15; i > -1; i--) {
            for (int j = 9; j > -1; j--) {
                if (GameBoard[i][j] == 1){
                    GameBoard[i][j] = 0;
                    GameBoard[i + 1][j] = 1;
                }
            }
        }
        if(movableBlock)
            tet->y++;
    }
    else {
        for (int  i = 0; i < 16; i++)
        {
            for (int j = 0; j < 10; j++) {
                if (GameBoard[i][j] == 1)
                    GameBoard[i][j] = 2;
            }
        }
    }
    return movable;
}

//this function moves a tetrimonio right
void move_tetrimonio_right(int GameBoard[16][10], struct tetrimonio* tet) {
    int movableBlock = 0;
    int movable = 1;
    if (tet->x + getTetrimonioWidth(tet->type) < 10)
    {
        movableBlock = 1;
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 9; j++) {
            if (GameBoard[i][j] == 1 && GameBoard[i][j + 1] == 2 //genau anschauen
                || GameBoard[i][j + 1] == 1 && j + 1 == 9) {
                movable = 0;
            }
        }
    }

    if (movable) {
        for (int i = 15; i > -1; i--) {
            for (int j = 9; j > -1; j--)
            {
                if (GameBoard[i][j] == 1 && j < 9) {
                    GameBoard[i][j] = 0;
                    GameBoard[i][j + 1] = 1;
                }
            }
        }
        if(movableBlock)
            tet->x++;
    }
}

//this function moves a tetrimonio left
void move_tetrimonio_left(int GameBoard[16][10], struct tetrimonio* tet) {
    int movable = 1;
    int movableBlock = 0;
    if (tet->x > 0)
    {
        movableBlock = 1;
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 1; j < 10; j++) {
            if (GameBoard[i][j] == 1 && GameBoard[i][j - 1] == 2 //genau anschauen
                || GameBoard[i][j - 1] == 1 && j - 1 == 0) {
                movable = 0;
            }
        }
    }

    if (movable) {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 10; j++)
            {
                if (GameBoard[i][j] == 1 && j > 0) {
                    GameBoard[i][j] = 0;
                    GameBoard[i][j - 1] = 1;
                }
            }
        }
        if (movableBlock)
        {
            tet->x--;
        }
    }
}

//this function returns the width of a tetrimonio with a specific number
int getTetrimonioWidth(int num) {
    switch (num)
    {
    case 0:
        return 4;
    case 1:
        return 3;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 3;
    }
}

//this function splices the array at a specific row
void spliceArray(int GameBoard[16][10], int row) {
    for (int i = row; i > -1; i--) {
        for (int j = 9; j > -1; j--) {
            if (i != 0)
            {
                GameBoard[i][j] = GameBoard[i - 1][j];
            }
            else {
                GameBoard[i][j] = 0;
            }
        }
    }
}

int getPoints(int GameBoard[16][10]) {
    int points = 0;
    int fullRow;
    for (int i = 0; i < 16; i++)
    {
        fullRow = 1;
        for (int j = 0; j < 10; j++) {
            if (GameBoard[i][j] != 2)
            {
                fullRow = 0;
            }
        }
        if (fullRow) {
            spliceArray(GameBoard, i);
            points += 25;
        }
    }
    return points;
}

int main()
{

    ALLEGRO_SAMPLE* sample = NULL;
    //init rand function
    srand(time(NULL));

    //init gameboard and tetrimonios
    int GameBoard[16][10] = { 0 };
    
    //init allegro components
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize keyboard!\n");
        return -1;
    }
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
    if (!al_init_font_addon()) {
        fprintf(stderr, "failed to initialize fonts!\n");
        return -1;
    }
    if (!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    sample = al_load_sample("Tetris.wav");

    if (!sample) {
        printf("Audio clip sample not loaded!\n");
        return -1;
    }

    //create display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 3);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(650, 800);
    ALLEGRO_FONT* font = al_create_builtin_font();


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

 
    int started = 0;
    struct tetrimonio tet;
    int score = 0;

    al_start_timer(timer);
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    while (1)
    {

        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch (event.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                rotate_tetrimonio(GameBoard, &tet);
                break;
            case ALLEGRO_KEY_RIGHT:
                move_tetrimonio_right(GameBoard, &tet);
                break;
            case ALLEGRO_KEY_LEFT:
                move_tetrimonio_left(GameBoard, &tet);
                break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            //generate and draw new tetrimonios
            if (started == 0) {
                tet = create_tetrimonio();
                started = 1;
                draw_tetrimonio(GameBoard, tet);
            }
            else {
                if (!move_tetrimonio(GameBoard, &tet))
                    started = 0;
            }
            
            char scoreString[50];
            sprintf(scoreString, "Score: %d", score);

            score += getPoints(GameBoard);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 510, 20, 0, "Next:");
            al_draw_text(font, al_map_rgb(255, 255, 255), 510, 70, 0, scoreString);

            for (int i = 0; i < 800; i+= 50) {
                for (int j = 0; j < 500; j += 50) {
                    if (GameBoard[i/50][j/50] != 0) {
                        al_draw_filled_rectangle((double)j, (double)i, (double)j + 50, (double)i + 50, al_map_rgb(0, 0, 255));
                    }
                }
            }

            al_draw_line(500, 0, 500, 800, al_map_rgb(255,255,255), 3);
            al_flip_display();

            redraw = false;


            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 10; j++) {
                    printf("%d ", GameBoard[i][j]);
                }
                printf("\n");
            }
            printf("--\n");
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}