#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>
#include <stdbool.h>

typedef enum enemyType {
    ENEMY1,
    ENEMY2,
    ENEMY3,
    ENEMY4,
    ENEMY5
} enemyType;

typedef struct enemy{
    int enemyX; 
    int enemyY;
    int width;
    int height;
    SDL_Rect rect;
    enemyType type;
    int speed;
    bool alive;
    int health;
} Enemy;

Enemy enemyCreate(int x, int y, int width, int height, enemyType type, int speed, int health);
void enemyMove(Enemy* enemy, int playerX, int playerY);
void enemyCombat(Enemy* enemy, int bulletX, int bulletY);

#endif // ENEMY_H