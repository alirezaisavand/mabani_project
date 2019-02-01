#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
#include<stdbool.h>
#include<stdlib.h>
#include"SDL.h"
#include "physics.h"

void save_game(Tank* tank1, Tank* tank2, int map_number);
void draw_tank(Tank* tank1, SDL_Renderer* renderer, int color);
void init_window(SDL_Renderer* renderer);
void quit_window(SDL_Window* window, SDL_Renderer * renderer);
int handle_events(Powerup* powerup, int* showmenu, Tank* tank1, Tank* tank2, Map* map, int map_number, int poweruptime);
void draw_bullet(SDL_Renderer* renderer, Bullet* bullet);
void draw_walls(SDL_Renderer* renderer, Wall* wall);
void show_score( SDL_Renderer* renderer, Tank* tank1, Tank* tank2);
void show_powerup(SDL_Renderer* renderer, Powerup* powerup);
void draw_powerup_bullet(SDL_Renderer* renderer, Powerup_bullet* powerup_bullet);
void draw_special_powerup(SDL_Renderer* renderer, Special_powerup* special_powerup);