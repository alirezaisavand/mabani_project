//in the name of Allah
#include"logic.h"

#ifdef main
#undef main
#endif /*main*/

int movement_collids_walls(Tank* tank, Wall* wall){
    double dis;
    if(wall -> x1 == wall -> x2)
        dis = abs(wall -> x1 - tank -> x);
    else
        dis = abs(wall -> y1 - tank -> y);
    double dis1, dis2, dx1 = tank -> x - wall -> x1, dy1 = tank -> y - wall -> y1;
    double dx2 = tank -> x - wall -> x2, dy2 = tank -> y - wall -> y2;
    dis1 = sqrt(dx1 * dx1 + dy1 * dy1);
    dis2 = sqrt(dx2 * dx2 + dy2 * dy2);
    if(dis1 > dis2)
        dis1 = dis2;
    if(dis1 <= (tank -> rad) + 2)
        return 1;
    if(dis <= (tank -> rad) + 2) {
        if(wall -> x1 == wall -> x2){
            if(tank -> y >= wall -> y1 && tank -> y <= wall -> y2)
                return 1;
            if(tank -> y >= wall -> y2 && tank -> y <= wall -> y1)
                return 1;
        }
        if(wall -> y1 == wall -> y2){
            if(tank -> x >= wall -> x1 && tank -> x <= wall -> x2)
                return 1;
            if(tank -> x >= wall -> x2 && tank -> x <= wall -> x1)
                return 1;
        }
    }
    return 0;
}

int movement_collids_walls_bullet(Bullet* bullet, Wall* wall){
    double dis;
    if(wall -> x1 == wall -> x2)
        dis = abs(wall -> x1 - bullet -> x);
    else
        dis = abs(wall -> y1 - bullet -> y);
    double dis1, dis2, dx1 = bullet -> x - wall -> x1, dy1 = bullet -> y - wall -> y1;
    double dx2 = bullet -> x - wall -> x2, dy2 = bullet -> y - wall -> y2;
    dis1 = sqrt(dx1 * dx1 + dy1 * dy1);
    dis2 = sqrt(dx2 * dx2 + dy2 * dy2);
    if(dis1 > dis2)
        dis1 = dis2;
    if(dis1 <= (bullet -> rad) + 3)
        return 1;
    if(dis <= (bullet -> rad) + 3) {
        if(wall -> x1 == wall -> x2){
            if(bullet -> y >= wall -> y1 && bullet -> y <= wall -> y2)
                return 1;
            if(bullet -> y >= wall -> y2 && bullet -> y <= wall -> y1)
                return 1;
        }
        if(wall -> y1 == wall -> y2){
            if(bullet -> x >= wall -> x1 && bullet -> x <= wall -> x2)
                return 1;
            if(bullet -> x >= wall -> x2 && bullet -> x <= wall -> x1)
                return 1;
        }
    }
    return 0;
}

int movement_collids_bullet_tank(Bullet* bullet, Tank* tank){
    int x1 = tank -> x, x2 = bullet -> x, y1 = tank -> y, y2 = bullet -> y;
    int r1 = tank -> rad, r2 = bullet -> rad;
    if((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2))
        return 1;
    return 0;
}

int movement_collids_tank_tank(Tank* tank1, Tank* tank2){
    int x1 = tank1 -> x, x2 = tank2 -> x, y1 = tank1 -> y, y2 = tank2 -> y;
    int r1 = tank1 -> rad, r2 = tank2 -> rad;
    if((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2))
        return 1;
    return 0;
}

int movement_collids_powerup_tank(Powerup* powerup, Tank* tank){
    int x1 = powerup -> x, x2 = tank -> x, y1 = powerup -> y, y2 = tank -> y;
    int r1 = powerup -> rad, r2 = tank -> rad;
    if((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2))
        return 1;
    return 0;
}

int movement_collids_powerup_walls(Powerup* powerup, Wall* wall){
    double dis;
    if(wall -> x1 == wall -> x2)
        dis = abs(wall -> x1 - powerup -> x);
    else
        dis = abs(wall -> y1 - powerup -> y);
    double dis1, dis2, dx1 = powerup -> x - wall -> x1, dy1 = powerup -> y - wall -> y1;
    double dx2 = powerup -> x - wall -> x2, dy2 = powerup -> y - wall -> y2;
    dis1 = sqrt(dx1 * dx1 + dy1 * dy1);
    dis2 = sqrt(dx2 * dx2 + dy2 * dy2);
    if(dis1 > dis2)
        dis1 = dis2;
    if(dis1 <= powerup -> rad)
        return 1;
    if(dis <= (powerup -> rad)) {
        if(wall -> x1 == wall -> x2){
            if(powerup -> y >= wall -> y1 && powerup -> y <= wall -> y2)
                return 1;
            if(powerup -> y >= wall -> y2 && powerup -> y <= wall -> y1)
                return 1;
        }
        if(wall -> y1 == wall -> y2){
            if(powerup -> x >= wall -> x1 && powerup -> x <= wall -> x2)
                return 1;
            if(powerup -> x >= wall -> x2 && powerup -> x <= wall -> x1)
                return 1;
        }
    }
    return 0;
}

int movement_collids_walls_powerup_bullet(Powerup_bullet* powerup_bullet, Wall* wall){
    double dis;
    if(wall -> x1 == wall -> x2)
        dis = abs(wall -> x1 - powerup_bullet -> x);
    else
        dis = abs(wall -> y1 - powerup_bullet -> y);
    double dis1, dis2, dx1 = powerup_bullet -> x - wall -> x1, dy1 = powerup_bullet -> y - wall -> y1;
    double dx2 = powerup_bullet -> x - wall -> x2, dy2 = powerup_bullet -> y - wall -> y2;
    dis1 = sqrt(dx1 * dx1 + dy1 * dy1);
    dis2 = sqrt(dx2 * dx2 + dy2 * dy2);
    if(dis1 > dis2)
        dis1 = dis2;
    if(dis1 <= powerup_bullet -> rad)
        return 1;
    if(dis <= (powerup_bullet -> rad)) {
        if(wall -> x1 == wall -> x2){
            if(powerup_bullet -> y >= wall -> y1 && powerup_bullet -> y <= wall -> y2)
                return 1;
            if(powerup_bullet -> y >= wall -> y2 && powerup_bullet -> y <= wall -> y1)
                return 1;
        }
        if(wall -> y1 == wall -> y2){
            if(powerup_bullet -> x >= wall -> x1 && powerup_bullet -> x <= wall -> x2)
                return 1;
            if(powerup_bullet -> x >= wall -> x2 && powerup_bullet -> x <= wall -> x1)
                return 1;
        }
    }
    return 0;
}

movement_collids_powerup_bullet_tank(Powerup_bullet* powerup_bullet, Tank* tank){
    int x1 = powerup_bullet -> x, x2 = tank -> x, y1 = powerup_bullet -> y, y2 = tank -> y;
    int r1 = powerup_bullet -> rad, r2 = tank -> rad;
    if((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2))
        return 1;
    return 0;

}


int movement_collids_special_powerup_tank(Special_powerup* special_powerup, Tank* tank){
    int x1 = special_powerup -> x, x2 = tank -> x, y1 = special_powerup -> y, y2 = tank -> y;
    int r1 = special_powerup -> rad, r2 = tank -> rad;
    if((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= (r1 + r2) * (r1 + r2))
        return 1;
    return 0;

}


int movement_collids_walls_special_powerup(Special_powerup* special_powerup, Wall* wall){
    double dis;
    if(wall -> x1 == wall -> x2)
        dis = abs(wall -> x1 - special_powerup -> x);
    else
        dis = abs(wall -> y1 - special_powerup -> y);
    double dis1, dis2, dx1 = special_powerup -> x - wall -> x1, dy1 = special_powerup -> y - wall -> y1;
    double dx2 = special_powerup -> x - wall -> x2, dy2 = special_powerup -> y - wall -> y2;
    dis1 = sqrt(dx1 * dx1 + dy1 * dy1);
    dis2 = sqrt(dx2 * dx2 + dy2 * dy2);
    if(dis1 > dis2)
        dis1 = dis2;
    if(dis1 <= special_powerup -> rad)
        return 1;
    if(dis <= (special_powerup -> rad)) {
        if(wall -> x1 == wall -> x2){
            if(special_powerup -> y >= wall -> y1 && special_powerup -> y <= wall -> y2)
                return 1;
            if(special_powerup -> y >= wall -> y2 && special_powerup -> y <= wall -> y1)
                return 1;
        }
        if(wall -> y1 == wall -> y2){
            if(special_powerup -> x >= wall -> x1 && special_powerup -> x <= wall -> x2)
                return 1;
            if(special_powerup -> x >= wall -> x2 && special_powerup -> x <= wall -> x1)
                return 1;
        }
    }
    return 0;

}