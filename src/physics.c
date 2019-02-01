//in the name of Allah
#include<stdio.h>
#include<SDL2_gfxPrimitives.h>
#include"SDL.h"
#include"physics.h"

#ifdef main
#undef main
#endif /*main*/

void move_tank(Powerup* powerup, Tank* tank1, Tank* tank2, int *dir, Map* map){
    double PI = 3.14159265;
    double deg_rad = PI * tank1 -> angle / 180.0;
    // printf("%d\n", *dir);
    double last_x = tank1 -> x, last_y = tank1 -> y;
    tank1 -> x += (*dir * 5 * cos(deg_rad));
    tank1 -> y -= (*dir * 5 * sin(deg_rad));
    for(int i = 0; i < map -> cnt_walls; i ++){
        if(movement_collids_walls(tank1, map -> walls + i)){
            tank1 -> x = last_x;
            tank1 -> y = last_y;
        }
    }
    if(movement_collids_tank_tank(tank1, tank2)){
        tank1 -> x = last_x;
        tank1 -> y = last_y;
    }
    if(powerup -> available == 1 && movement_collids_powerup_tank(powerup, tank1)){
        powerup -> available = 0;
        tank1 -> power = 1;
    }
}

void turn_tank(Tank* tank, int *dir){
    tank -> angle += *dir * 5;
}

int fire(Tank* tank, Tank* tank2, Map* map){
    int sp = -1;
    for(int i = 0; i < 5; i ++){
        if(*(tank -> mark + i) == 0)
            sp = i;
    }
    if(sp == -1)
        return 0;
    Bullet* bullet = tank -> bullets + sp;
    *(tank -> mark + sp) = 1;
    double PI = 3.14159265;
    bullet -> rad = 3;
    double deg_rad = PI * tank -> angle / 180.0;
    double first_x = tank -> x + (tank -> rad + bullet -> rad + 1) * cos(deg_rad), first_y = tank -> y - (tank -> rad + bullet -> rad + 1) * sin(deg_rad);
    bullet -> x = first_x;
    bullet -> y = first_y;
    bullet -> angle = tank -> angle;
    bullet -> time = 0;
    bullet -> num = tank -> cnt_bullet;
    tank -> cnt_bullet ++;
    for(int i = 0; i < map ->  cnt_walls; i ++){
        Wall* wall = map -> walls + i;
        if(movement_collids_walls_bullet(bullet, wall)){
            (tank2 -> score) ++;
            return 1;
        }
    }
    return 0;
}

const int inf = 1000;

int fire_bomb(Tank* tank, Tank* tank2, Map* map){
    Special_powerup* special_powerup = tank -> special_powerups;
    special_powerup -> rad = 5;
    double PI = 3.14159265;
    double deg_rad = PI * tank -> angle / 180.0;
    double first_x = tank -> x + (tank -> rad + special_powerup -> rad + 1) * cos(deg_rad), first_y = tank -> y - (tank -> rad + special_powerup -> rad + 1) * sin(deg_rad);
    special_powerup -> x = first_x;
    special_powerup -> y = first_y;
    special_powerup -> angle = tank -> angle;
    special_powerup -> available = 1;
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* power_bullet = (special_powerup -> powerup_bullets) + i;
        power_bullet -> time = inf;
    }
    for(int i = 0; i < map -> cnt_walls; i ++){
        Wall* wall = map -> walls + i;
        if(movement_collids_walls_special_powerup(special_powerup, wall)){
            (tank2 -> score) ++;
            return 1;
        }
    }
    return 0;
}

int move_special_powerup(Special_powerup* special_powerup, Tank* tank1, Tank* tank2, Map* map){
    double PI = 3.14159265;
    double deg_rad = PI * special_powerup -> angle / 180.0;
    double last_x = special_powerup -> x, last_y = special_powerup -> y, last_angle = special_powerup -> angle;
    special_powerup -> x += 6 * cos(deg_rad);
    special_powerup -> y -= 6 * sin(deg_rad);
    if(movement_collids_special_powerup_tank(special_powerup, tank1)){
        (tank2 -> score) ++;
        return 1;
    }
    if(movement_collids_special_powerup_tank(special_powerup, tank2)){
        (tank1 -> score) ++;
        return 1;
    }
    int fl = 0;
    for(int i = 0; i < map -> cnt_walls; i ++){
        Wall* wall = map -> walls + i;
        if(movement_collids_walls_special_powerup(special_powerup, wall)){
            fl = 1;
            special_powerup -> x = last_x;
            special_powerup -> y = last_y;
            if(wall -> x1 == wall -> x2)
                special_powerup -> angle = 540 - (special_powerup -> angle);
            else
                special_powerup -> angle = 360 - (special_powerup -> angle);
        }

    }
    if(fl == 1){
        double deg_rad = PI * special_powerup -> angle / 180.0;
        int last_x = special_powerup -> x, last_y = special_powerup -> y;
        special_powerup -> x += 6 * cos(deg_rad);
        special_powerup -> y -= 6 * sin(deg_rad);
        for(int i = 0; i < map -> cnt_walls; i ++){
            Wall* wall = map -> walls + i;
            if(movement_collids_walls_special_powerup(special_powerup, wall)){
                special_powerup -> angle -= 180;
                break;
            }

        }
        special_powerup -> x = last_x;
        special_powerup -> y = last_y;
    }
    return 0;
}

void fire_powerup(Special_powerup* special_powerup){
    special_powerup -> available = 0;
    for(int i = 0; i < 8; i ++){
        Powerup_bullet* power_bullet = (special_powerup -> powerup_bullets) + i;
        power_bullet -> angle = 45 * i;
        power_bullet -> x = special_powerup -> x;
        power_bullet -> y = special_powerup -> y;
        power_bullet -> time = 0;
        power_bullet -> rad = 3;
    }
}

int move_bullet(SDL_Renderer *renderer,int *f, Map* map, Bullet* bullet, Tank* tank1, Tank* tank2){
    double PI = 3.14159265;
    double deg_rad = PI * bullet -> angle / 180.0;
    double last_x = bullet -> x, last_y = bullet -> y, last_angle = bullet -> angle;
    bullet -> x += 6 * cos(deg_rad);
    bullet -> y -= 6 * sin(deg_rad);
    if(movement_collids_bullet_tank(bullet, tank1)){
        (tank2 -> score) ++;
        return 1;
    }
    if(movement_collids_bullet_tank(bullet, tank2)){
        (tank1 -> score) ++;
        return 1;
    }
    int fl = 0;
    for(int i = 0; i < map -> cnt_walls; i ++){
        Wall* wall = map -> walls + i;
        if(movement_collids_walls_bullet(bullet, wall)){
            fl = 1;
            bullet -> x = last_x;
            bullet -> y = last_y;
            if(wall -> x1 == wall -> x2)
                bullet -> angle = 540 - (bullet -> angle);
            else
                bullet -> angle = 360 - (bullet -> angle);
        }

    }
    if(fl == 1){
        double deg_rad = PI * bullet -> angle / 180.0;
        int last_x = bullet -> x, last_y = bullet -> y;
        bullet -> x += 6 * cos(deg_rad);
        bullet -> y -= 6 * sin(deg_rad);
        for(int i = 0; i < map -> cnt_walls; i ++){
            Wall* wall = map -> walls + i;
            if(movement_collids_walls_bullet(bullet, wall)){
                bullet -> angle -= 180;
                break;
            }

        }
        bullet -> x = last_x;
        bullet -> y = last_y;
    }
    return 0;
}

int move_powerup_bullet(Powerup_bullet* powerup_bullet, Tank* tank1, Tank* tank2, Map* map){
    double PI = 3.14159265;
    double deg_rad = PI * powerup_bullet -> angle / 180.0;
    double last_x = powerup_bullet -> x, last_y = powerup_bullet -> y;
    powerup_bullet -> x += 6 * cos(deg_rad);
    powerup_bullet -> y -= 6 * sin(deg_rad);
    if(movement_collids_powerup_bullet_tank(powerup_bullet, tank1)){
        tank2 -> score ++;
        return 1;
    }
    if(movement_collids_powerup_bullet_tank(powerup_bullet, tank2)){
        tank1 -> score ++;
        return 1;
    }
    for(int i = 0; i < map -> cnt_walls; i ++){
        Wall* wall = map -> walls + i;
        if(movement_collids_walls_powerup_bullet(powerup_bullet, wall)){
            powerup_bullet -> x = last_x;
            powerup_bullet -> y = last_y;
        }
    }
    return 0;
}