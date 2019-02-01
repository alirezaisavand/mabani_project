//in the name of Allah

#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
#include<stdbool.h>
#include<stdlib.h>
#include"SDL.h"
#include"structs.h"
#include<math.h>

int movement_collids_walls(Tank* tank, Wall* wall);
int movement_collids_walls_bullet(Bullet* bullet, Wall* wall);
int movement_collids_bullet_tank(Bullet* bullet, Tank* tank);
int movement_collids_tank_tank(Tank* tank1, Tank* tank2);
int movement_collids_powerup_tank(Powerup* powerup, Tank* tank);
int movement_collids_powerup_walls(Powerup* powerup, Wall* wall);
int movement_collids_walls_powerup_bullet(Powerup_bullet* powerup_bullet, Wall* wall);
int movement_collids_powerup_bullet_tank(Powerup_bullet* powerup_bullet, Tank* tank);
int movement_collids_special_powerup_tank(Special_powerup* special_powerup, Tank* tank);
int movement_collids_walls_special_powerup(Special_powerup* special_powerup, Wall* wall);