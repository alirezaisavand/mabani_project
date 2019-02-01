#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
//#include <SDL2_gfxPrimitives.h>
#include"SDL.h"
#include"view.h"
#include<time.h>

#ifdef main
#undef main
#endif /*main*/

void save_game(Tank* tank1, Tank* tank2, int map_number){
    FILE* file = fopen("game.txt", "w");
    fprintf(file, "%d\n", map_number);
    fprintf(file, "%d %lf %lf %lf %lf %d %d\n", tank1 -> power, tank1 -> x, tank1 -> y, tank1 -> rad, tank1 -> angle, tank1 -> cnt_bullet, tank1 -> score);
    printf("%lf\n", tank1->x);

    for(int i = 0; i < 5; i ++){
        fprintf(file, "%d\n", *(tank1 -> mark + i));
        if(*(tank1 -> mark + i) == 1){
            Bullet* bullet = (tank1 -> bullets + i);
            fprintf(file, "%lf %lf %lf %lf %lf %lf\n", bullet -> x, bullet -> y, bullet -> time, bullet -> rad, bullet -> angle, bullet -> num);
        }
    }
    Special_powerup* special_powerup = tank1 -> special_powerups;
    fprintf(file, "%lf %lf %lf %lf %lf\n", (special_powerup -> x), (special_powerup -> y), (special_powerup -> angle), (special_powerup -> rad), (special_powerup -> available));
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* powerup_bullet = (tank1 -> special_powerups) -> powerup_bullets + i;
        fprintf(file, "%lf %lf %lf %lf %lf\n", (powerup_bullet -> x), (powerup_bullet -> y), (powerup_bullet -> angle), (powerup_bullet -> rad), (powerup_bullet -> time));
    }
    fprintf(file, "%d %lf %lf %lf %lf %d %d\n", tank2 -> power, tank2 -> x, tank2 -> y, tank2 -> rad, tank2 -> angle, tank2 -> cnt_bullet, tank2 -> score);
    for(int i = 0; i < 5; i ++){
        fprintf(file, "%d\n", *(tank2 -> mark + i));
        if(*(tank2 -> mark + i) == 1){
            Bullet* bullet = (tank2 -> bullets + i);
            fprintf(file, "%lf %lf %lf %lf %lf %lf\n", bullet -> x, bullet -> y, bullet -> time, bullet -> rad, bullet -> angle, bullet -> num);
        }
    }
    Special_powerup* special_powerup2 = tank2 -> special_powerups;
    fprintf(file, "%lf %lf %lf %lf %lf\n", (special_powerup2 -> x), (special_powerup2 -> y), (special_powerup2 -> angle), (special_powerup2 -> rad), (special_powerup2 -> available));
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* powerup_bullet = (tank2 -> special_powerups) -> powerup_bullets + i;
        fprintf(file, "%lf %lf %lf %lf %lf\n", (powerup_bullet -> x), (powerup_bullet -> y), (powerup_bullet -> angle), (powerup_bullet -> rad), (powerup_bullet -> time));
    }
    fclose(file);
}

void draw_tank(Tank* tank, SDL_Renderer* renderer, int color){
    filledCircleRGBA(renderer, tank->x, tank->y, tank->rad, 220 * color, 20 + 220 * (1 - color), 60, 128);
    if(tank -> power == 1)
        filledCircleRGBA(renderer, tank -> x, tank -> y, tank -> rad - 2, 100, 100, 10, 128);
    double PI = 3.14159265;
    double deg_rad = PI * tank -> angle / 180.0;
    double x2 = tank -> x + tank -> rad * cos(deg_rad), y2 = tank -> y - tank -> rad * sin(deg_rad);
    thickLineRGBA(renderer, tank -> x, tank -> y, x2, y2, 5, 0, 0, 0, 128);
}

void init_window(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 128);
    SDL_RenderClear(renderer);
}

void quit_window(SDL_Window* window, SDL_Renderer * renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int handle_events(Powerup* powerup, int* showmenu, Tank* tank1, Tank* tank2, Map* map, int map_number, int poweruptime){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_KEYDOWN && state[SDL_SCANCODE_ESCAPE]) {
            *showmenu = 1;
            return 1;
        }
        int val1 = 0, val2 = 0;
        int *dir1 = &val1, *dir2 = &val2;
        if(state[SDL_SCANCODE_J])
            *dir1 = -1;
        if(state[SDL_SCANCODE_U])
            *dir1 = 1;
        if(state[SDL_SCANCODE_W])
            *dir2 = 1;
        if(state[SDL_SCANCODE_S])
            *dir2 = -1;
        if(state[SDL_SCANCODE_L])
            save_game(tank1, tank2, map_number);
        move_tank(powerup, tank1, tank2, dir1, map);
        move_tank(powerup, tank2, tank1, dir2, map);
        *dir1 = 0;
        *dir2 = 0;
        if(state[SDL_SCANCODE_K])
            *dir1 = -1;
        if(state[SDL_SCANCODE_H])
            *dir1 = 1;
        if(state[SDL_SCANCODE_D])
            *dir2 = -1;
        if(state[SDL_SCANCODE_A])
            *dir2 = 1;
        turn_tank(tank1, dir1);
        turn_tank(tank2, dir2);
        if(e.type == SDL_KEYDOWN && state[SDL_SCANCODE_SPACE]){
            if(tank1 -> power == 0) {
                int ret = fire(tank1, tank2, map);
                if(ret == 1)
                    return 2;
            }
            if(tank1 -> power == 2){
                tank1 -> power = 0;
                fire_powerup(tank1 -> special_powerups);
            }
            if(tank1 -> power == 1) {
                int ret = fire_bomb(tank1, tank2, map);
                tank1 -> power = 2;
                if(ret == 1)
                    return 2;
            }
        }
        if(e.type == SDL_KEYDOWN && state[SDL_SCANCODE_TAB]){
            if(tank2 -> power == 0){
                int ret = fire(tank2, tank1, map);
                if(ret == 1)
                    return 2;
            }
            if(tank2 -> power == 2){
                tank2 -> power = 0;
                fire_powerup(tank2 -> special_powerups);
            }
            if(tank2 -> power == 1){
                int ret = fire_bomb(tank2, tank1, map);
                tank2 -> power = 2;
                if(ret == 1)
                    return 2;
            }
        }
    }
    return 1;
}

void draw_special_powerup(SDL_Renderer* renderer, Special_powerup* special_powerup){
    srand(time(0));
    filledCircleRGBA(renderer, special_powerup -> x, special_powerup -> y, special_powerup -> rad, rand() % 255, rand() % 255, rand() % 255, 128);
}

void draw_bullet(SDL_Renderer* renderer, Bullet* bullet){
    filledCircleRGBA(renderer, bullet -> x, bullet -> y, bullet -> rad, 0, 0, 0, 255 - 2 * (bullet -> time));
}

void draw_walls(SDL_Renderer* renderer, Wall* wall){
    thickLineRGBA(renderer, wall -> x1, wall -> y1, wall -> x2, wall -> y2, 5, 0, 0, 0, 128);

}

void show_score(SDL_Renderer* renderer, Tank* tank1, Tank* tank2){
    char score1[10] = {'P', 'L', 'A', 'Y', 'E', 'R', '1', ':', '0' + tank1 -> score, '\0'};
    char score2[10] = {'P', 'L', 'A', 'Y', 'E', 'R', '2', ':', '0' + tank2 -> score, '\0'};
    stringRGBA(renderer, 5, 880, score1, 0, 0, 0, 128);
    stringRGBA(renderer, 100, 880, score2, 0, 0, 0, 128);
    filledCircleRGBA(renderer, 40, 860, 15, 0, 240, 60, 128);
    thickLineRGBA(renderer, 40, 860, 55, 860, 2, 0, 0, 0, 128);
    filledCircleRGBA(renderer, 135, 860, 15, 220, 20, 60, 128);
    thickLineRGBA(renderer, 135, 860, 120, 860, 2, 0, 0, 0, 128);

}

void show_powerup(SDL_Renderer* renderer, Powerup* powerup){
    filledCircleRGBA(renderer, powerup -> x, powerup -> y, powerup -> rad, 200, 0, 0, 255);
}

void draw_powerup_bullet(SDL_Renderer* renderer, Powerup_bullet* powerup_bullet){
    filledCircleRGBA(renderer, powerup_bullet -> x, powerup_bullet -> y, powerup_bullet -> rad, rand() % 255, rand() % 255, rand() % 255, 128);
}