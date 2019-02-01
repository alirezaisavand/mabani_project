//in the name of Allah
#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
#include<stdbool.h>
#include<stdlib.h>
#include "logic.h"
//#include <SDL2_gfxPrimitives.h>
#include"SDL.h"

void move_tank(Powerup* powerup, Tank* tank1, Tank* tank2, int *dir, Map* map);
void turn_tank(Tank* tank, int *dir);
int fire(Tank* tank, Tank* tank2, Map* map);
int fire_bomb(Tank* tank, Tank* tank2, Map* map);
int move_bullet(SDL_Renderer* renderer, int* f, Map* map, Bullet* bullet, Tank* tank1, Tank* tank2);
void fire_powerup(Special_powerup* special_powerup);
int move_powerup_bullet(Powerup_bullet* powerup_bullet, Tank* tank1, Tank* tank2, Map* map);
int move_special_powerup(Special_powerup* special_powerup, Tank* tank1, Tank* tank2, Map* map);