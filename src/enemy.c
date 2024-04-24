#include "enemy.h"

Enemy enemyCreate(int x, int y, int width, int height, enemyType type, int speed, int health) {
    Enemy enemy;

    enemy.enemyX = x;
    enemy.enemyY = y;
    enemy.width = width;
    enemy.height = height;
    enemy.rect = (SDL_Rect) {x, y, width, height};
    enemy.type = type;
    enemy.speed = speed;
    enemy.alive = true;
    enemy.health = health;

    return enemy;
}
void enemyMove(Enemy* enemy, int playerX, int playerY) {
    if (enemy->alive == true) {
        if (enemy->enemyX < playerX) {
            enemy->enemyX += enemy->speed;
            enemy->rect.x = enemy->enemyX;
        }
        if (enemy->enemyX > playerX) {
            enemy->enemyX -= enemy->speed;
            enemy->rect.x = enemy->enemyX;
        }
        if (enemy->enemyY < playerY) {
            enemy->enemyY += enemy->speed;
            enemy->rect.y = enemy->enemyY;
        }
        if (enemy->enemyY > playerY) {
            enemy->enemyY -= enemy->speed;
            enemy->rect.y = enemy->enemyY;
        }
    }
}
void enemyCombat(Enemy* enemy, int bulletX, int bulletY){
    if (enemy->alive == true) {
        if (enemy->enemyX == bulletX && enemy->enemyY == bulletY) {
            enemy->health -= 5;
        }
        if(enemy->health <= 0){
            enemy->alive == false;
        }
    }
}
