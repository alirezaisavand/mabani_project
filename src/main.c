//
// Created by Lenovo on 12/22/2018.
//in the name of Allah
//
#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
//#include <SDL2_gfxPrimitives.h>
#include"SDL.h"
#include"view.h"
#ifdef main
#undef main
#endif /*main*/


const int MAX_BULLET = 5, MAX_TIME = 100;

void read_map_file(Map* map, int number){
    FILE * file;
    char file_number = '1' + number;
    char file_name[9] = {'m', 'a', 'p', file_number, '.', 't', 'x', 't', '\0'};
    file = fopen(file_name, "r");
    int cnt_wall;
    fscanf(file, "%d", &cnt_wall);
    map -> cnt_walls = cnt_wall;
    map -> walls = malloc(sizeof(Wall) * cnt_wall);
    for(int i = 0; i < cnt_wall; i ++){
        int x, y, xx, yy;
        fscanf(file, "%d %d %d %d", &x, &y, &xx, &yy);
        (map -> walls + i) -> x1 = 100 * x;
        (map -> walls + i) -> x2 = 100 * xx;
        (map -> walls + i) -> y1 = 100 * y;
        (map -> walls + i) -> y2 = 100 * yy;
    }
}

void new_game(Tank* tank_1, Tank* tank_2, Map* map, int file_number){
    read_map_file(map, file_number);
    int fl = 1;
    while(fl){
        fl = 0;
        tank_1 -> x = rand() % 500 + 50;
        tank_1 -> y = rand() % 400 + 50;
        for(int i = 0; i < map -> cnt_walls; i ++)
            if(movement_collids_walls(tank_1, map -> walls + i))
                fl = 1;
    }
    fl = 1;
    while(fl){
        fl = 0;
        tank_2 -> x = rand() % 500 + 50;
        tank_2 -> y = rand() % 400 + 50;
        if(movement_collids_tank_tank(tank_1, tank_2))
            fl = 1;
        for(int i = 0; i < map -> cnt_walls; i ++)
            if(movement_collids_walls(tank_2, map -> walls + i))
                fl = 1;
    }
    tank_1 -> power = 0;
    tank_1 -> rad = 23;
    tank_1 -> angle = rand() % 360;
    tank_1 -> cnt_bullet = 0;
    tank_1 -> bullets = malloc(sizeof(Bullet) * MAX_BULLET);
    tank_1 -> mark = malloc(sizeof(int) * MAX_BULLET);
    tank_1 -> special_powerups = malloc(sizeof(Special_powerup));
    (tank_1 -> special_powerups) -> powerup_bullets = malloc(sizeof(Powerup_bullet) * 8);
    tank_2 -> power = 0;
    tank_2 -> rad = 23;
    tank_2 -> angle = rand() % 360;
    tank_2 -> cnt_bullet = 0;
    tank_2 -> bullets = malloc(sizeof(Bullet) * MAX_BULLET);
    tank_2 -> mark = malloc(sizeof(int) * MAX_BULLET);
    tank_2 -> special_powerups = malloc(sizeof(Special_powerup));
    (tank_2 -> special_powerups) -> powerup_bullets = malloc(sizeof(Powerup_bullet) * 8);
    for(int i = 0; i < MAX_BULLET; i ++){
        *((tank_1 -> mark) + i) = 0;
        *((tank_2 -> mark) + i) = 0;
    }
}

void load_game(Tank* tank1, Tank* tank2, Map* map){
    FILE* file = fopen("game.txt", "r+");
    int number;
    fscanf(file, "%d", &number);
    read_map_file(map, number);
    fscanf(file, "%d %lf %lf %lf %lf %d %d", &(tank1 -> power), &(tank1 -> x), &(tank1 -> y), &(tank1 -> rad), &(tank1 -> angle), &(tank1 -> cnt_bullet), &(tank1 -> score));
    for(int i = 0; i < MAX_BULLET; i ++) {
        fscanf(file, "%d\n", tank1 -> mark + i);
        if(*(tank1 -> mark + i) == 1){
            fscanf(file, "%lf %lf %lf %lf %lf %lf", &((tank1->bullets + i)->x), &((tank1->bullets + i)->y),
               &((tank1->bullets + i)->time), &((tank1->bullets + i)->rad), &((tank1->bullets + i)->angle),
               &((tank1->bullets + i)->num));
        }
    }
    Special_powerup* special_powerup = tank1 -> special_powerups;
    fscanf(file, "%lf %lf %lf %lf %lf\n", &(special_powerup -> x), &(special_powerup -> y), &(special_powerup -> angle), &(special_powerup -> rad), &(special_powerup -> available));
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* powerup_bullet = (tank1 -> special_powerups) -> powerup_bullets + i;
        fscanf(file, "%lf %lf %lf %lf %lf\n", &(powerup_bullet -> x), &(powerup_bullet -> y), &(powerup_bullet -> angle), &(powerup_bullet -> rad), &(powerup_bullet -> time));
    }
    fscanf(file, "%d %lf %lf %lf %lf %d %d", &(tank2 -> power), &(tank2 -> x), &(tank2 -> y), &(tank2 -> rad), &(tank2 -> angle), &(tank2 -> cnt_bullet), &(tank2 -> score));
    for(int i = 0; i < MAX_BULLET; i ++) {
        fscanf(file, "%d\n", tank2 -> mark + i);
        if(*(tank2 -> mark + i) == 1){
            fscanf(file, "%lf %lf %lf %lf %lf %lf", &((tank2->bullets + i)->x), &((tank2->bullets + i)->y),
               &((tank2->bullets + i)->time), &((tank2->bullets + i)->rad), &((tank2->bullets + i)->angle),
               &((tank2->bullets + i)->num));
        }
    }

    Special_powerup* special_powerup2 = tank2 -> special_powerups;
    fscanf(file, "%lf %lf %lf %lf %lf\n", &(special_powerup2 -> x), &(special_powerup2 -> y), &(special_powerup2 -> angle), &(special_powerup2 -> rad), &(special_powerup2 -> available));
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* powerup_bullet = (tank2 -> special_powerups) -> powerup_bullets + i;
        fscanf(file, "%lf %lf %lf %lf %lf\n", &(powerup_bullet -> x), &(powerup_bullet -> y), &(powerup_bullet -> angle), &(powerup_bullet -> rad), &(powerup_bullet -> time));
    }
    fclose(file);
}

int t = 0;

int menu(int* f, SDL_Renderer *renderer, Tank* tank1, Tank* tank2, Map* map, int* winner_tank, int* finish_point, int* file_number){
    int now = 0;
    while(1){
        SDL_RenderSetScale(renderer, 2, 2);
        char winner_num = '0' + *winner_tank;
        char winner_out[10] = {'T', 'A', 'N', 'K', winner_num, ' ', 'W', 'I', 'N', '\0'};
        int x1 = 180, y1 = 45;
        if(*winner_tank != 0) {
            t ++;
            if(t % 300 < 150) {
                stringRGBA(renderer, x1 - 10, y1 - 20, winner_out, 220 * (*winner_tank - 1), 220 * (2 - *winner_tank) + 20, 60, 128);
                filledCircleRGBA(renderer, x1 + 80, y1 - 20, 10, 220 * (*winner_tank - 1), 220 *
                (2 - *winner_tank) + 20, 60, 128);
                thickLineRGBA(renderer, x1 + 80, y1 - 20, x1 + 90, y1 - 20, 2, 0, 0, 0, 128);
            }
        }
        boxRGBA(renderer, 0, 0, 900, 900, 150, 150, 150, 128);
        stringRGBA(renderer, x1, y1, "START GAME", 0, 0, 0, 128);
        stringRGBA(renderer, x1, y1 + 14, "LOAD GAME", 0, 0, 0, 128);
        stringRGBA(renderer, x1, y1 + 28, "QUIT GAME", 0, 0, 0, 128);
        boxRGBA(renderer, x1 - 10, y1 - 4, x1 + 90, y1 - 4 + 14, 200, 200, 200, 128);
        boxRGBA(renderer, x1 - 10, y1 - 4 + 14, x1 + 90, y1 - 4 + 28, 200, 200, 200, 128);
        boxRGBA(renderer, x1 - 10, y1 - 4 + 28, x1 + 90, y1 - 4 + 42, 200, 200, 200, 128);
        boxRGBA(renderer, x1 - 10, 14 * now + y1 - 4, x1 + 90, 14 * now + 14 + y1 - 4, 100, 100, 100, 128);

        SDL_RenderSetScale(renderer, 1.0, 1.0);
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && *winner_tank == 0)
                return 0;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                if (now == 2)
                    *f = 0;
                if(now == 1){
                    *winner_tank = 0;
                    load_game(tank1, tank2, map);
                }
                if(now == 0){
                    *winner_tank = 0;
                    *file_number = 1;
                    new_game(tank1, tank2, map, *file_number);
                    tank1 -> score = 0;
                    tank2 -> score = 0;
                }
                return 0;
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
                now = (now + 1) % 3;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
                now = (now + 2) % 3;
        }
        SDL_RenderPresent(renderer);
    }
}

void new_powerup(Powerup* powerup, Tank* tank_1, Tank* tank_2, Map* map){
    powerup -> available = 1;
    powerup -> rad = 5;
    int fl = 1;
    while(fl){
        fl = 0;
        powerup -> x = rand() % 600 + 50;
        powerup -> y = rand() % 600 + 50;
        if(movement_collids_powerup_tank(powerup, tank_2))
            fl = 1;
        if(movement_collids_powerup_tank(powerup, tank_1))
            fl = 1;
        for(int i = 0; i < map -> cnt_walls; i ++)
            if(movement_collids_powerup_walls(powerup, map -> walls + i))
                fl = 1;
    }
}

int main(int args, char* argv[]){
    srand(time(0));
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            0,
            0,// initial y position
            900,
            900,
            SDL_WINDOW_ALLOW_HIGHDPI                  // flags - see below
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    Tank* tank_1 = malloc(sizeof(Tank) * 1);
    Tank* tank_2 = malloc(sizeof(Tank) * 1);
    Powerup * powerup = malloc(sizeof(Powerup));
    tank_1 -> score = 0;
    tank_2 -> score = 0;
    int file_number = 0;
    Map* map = malloc(sizeof(Map) * 1);
    new_game(tank_1, tank_2, map, file_number);
    int f = 1;
    int showmenu = 1;
    int winner_tank = 0;
    int FINISH_POINT = 5;
    int cnt_files = 3;
    int cycle = 0;
    int POWERUP_TIME = 20;
    while(f) {
        init_window(renderer);
        show_score(renderer, tank_1, tank_2);
        f = handle_events(powerup, &showmenu, tank_1, tank_2, map, file_number, POWERUP_TIME);//(map);
        if((tank_1 -> score) == FINISH_POINT){
            showmenu = 1;
            winner_tank = 1;
            file_number = 1;
            new_game(tank_1, tank_2, map, file_number);
            tank_1 -> score = 0;
        }
        if((tank_2 -> score) == FINISH_POINT){
            showmenu = 1;
            winner_tank = 2;
            file_number = 1;
            new_game(tank_1, tank_2, map, file_number);
            tank_2 -> score = 0;
        }
        if(showmenu){
            showmenu = menu(&f, renderer, tank_1, tank_2, map, &winner_tank, &FINISH_POINT, &file_number);
            continue;
        }
        if(f == 2){
            file_number ++;
            file_number %= cnt_files;
            new_game(tank_1, tank_2, map, file_number);
            f = 1;
        }
        cycle ++;
        cycle %= 1000;
        if(cycle % 1000 == 1){
            new_powerup(powerup, tank_1, tank_2, map);
        }
        if(cycle % 1000 == 400){
            powerup -> available = 0;
        }
        draw_tank(tank_1, renderer, 0);
        draw_tank(tank_2, renderer, 1);
        if(powerup -> available == 1)
            show_powerup(renderer, powerup);
        for(int i = 0; i < MAX_BULLET; i ++){
            if(*((tank_1 -> mark) + i) == 1){
                (tank_1 -> bullets + i) -> time ++;
                int collids = move_bullet(renderer, &f, map, tank_1 -> bullets + i, tank_1, tank_2);
                if(collids == 1){
                    file_number ++;
                    file_number %= cnt_files;
                    new_game(tank_1, tank_2, map, file_number);
                }
                draw_bullet(renderer, (tank_1 -> bullets + i));
            }
            if((tank_1 -> bullets + i) -> time == MAX_TIME)
                *((tank_1 -> mark) + i) = 0;
        }
        for(int i = 0; i < MAX_BULLET; i ++){
            if(*((tank_2 -> mark) + i) == 1){
                (tank_2 -> bullets + i) -> time ++;
                int collids = move_bullet(renderer, &f, map, tank_2 -> bullets + i, tank_1, tank_2);
                if(collids == 1) {
                    file_number ++;
                    file_number %= cnt_files;
                    new_game(tank_1, tank_2, map, file_number);
                }
                draw_bullet(renderer, (tank_2 -> bullets + i));
            }
            if((tank_2 -> bullets + i) -> time == MAX_TIME)
                *((tank_2 -> mark) + i) = 0;

        }
        if((tank_1 -> special_powerups) -> available == 1){
            int collids = move_special_powerup(tank_1 -> special_powerups, tank_1, tank_2, map);
            if(collids == 1){
                file_number ++;
                file_number %= cnt_files;
                new_game(tank_1, tank_2, map, file_number);
            }
            draw_special_powerup(renderer, tank_1 -> special_powerups);
        }
        for(int i = 0; i < 8; i ++) {
            Powerup_bullet *powerup_bullet = ((tank_1 -> special_powerups) -> powerup_bullets) + i;
            if (powerup_bullet-> time < POWERUP_TIME){
                (powerup_bullet -> time) ++;
                int collids = move_powerup_bullet(powerup_bullet, tank_1, tank_2, map);
                if(collids == 1){
                    file_number ++;
                    file_number %= cnt_files;
                    new_game(tank_1, tank_2, map, file_number);
                }
                draw_powerup_bullet(renderer, powerup_bullet);
            }
        }
        if((tank_2 -> special_powerups) -> available == 1){
            int collids = move_special_powerup(tank_2 -> special_powerups, tank_1 , tank_2, map);
            if(collids == 1){
                file_number ++;
                file_number %= cnt_files;
                new_game(tank_1, tank_2, map, file_number);
            }
            draw_special_powerup(renderer, tank_2 -> special_powerups);
        }
        for(int i = 0; i < 8; i ++) {
            Powerup_bullet *powerup_bullet = ((tank_2 -> special_powerups) -> powerup_bullets) + i;
            if (powerup_bullet-> time < POWERUP_TIME){
                (powerup_bullet -> time) ++;
                int collids = move_powerup_bullet(powerup_bullet, tank_1, tank_2, map);
                if(collids == 1){
                    file_number ++;
                    file_number %= cnt_files;
                    new_game(tank_1, tank_2, map, file_number);
                }
                draw_powerup_bullet(renderer, powerup_bullet);
            }
        }
        for(int i = 0; i < map -> cnt_walls; i ++)
            draw_walls(renderer, ((map -> walls) + i));
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
    quit_window(window, renderer);
    return 0;
}

