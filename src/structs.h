//In the name of Allah

typedef struct{
    double x, y, time, rad, angle, num;
} Bullet;

typedef struct{
    double x, y, angle, rad, time;
} Powerup_bullet;

typedef struct{
    int available, rad;
    double x, y, angle;
} Powerup;

typedef struct{
    double x, y, angle, rad, available;
    Powerup_bullet* powerup_bullets;
} Special_powerup;

typedef struct{
    double x;
    double y;
    double rad;
    double angle;
    int cnt_bullet;
    int score;
    Bullet* bullets;
    int power;
    int* mark;
    Special_powerup* special_powerups;
} Tank;

typedef struct{
    int x1, x2, y1, y2;
} Wall;

typedef struct{
    Tank* tanks;
    Wall* walls;
    int cnt_walls;
} Map;

