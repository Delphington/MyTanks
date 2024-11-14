#include <iostream>
#include "Bullet.h"
#include "../model/Card.h" // Включаем Card.h для работы с классом Card

// Конструктор
Bullet::Bullet(int X, int Y, int direction, int player)
        : dx(0),
          dy(0),
          w(Config::BULLET_WIDTH),
          h(Config::BULLET_HEIGHT),
          p1life(true),
          p2life(true),
          life(true),
          x(X),
          y(Y),
          pl(player){

// Определение направления
    switch (direction) {
        case 1:
            dx = -0.3; // Стрельба влево
            break;
        case 2:
            dx = 0.3; // Стрельба вправо
            break;
        case 3:
            dy = -0.3; // Стрельба вверх
            break;
        case 4:
            dy = 0.3; // Стрельба вниз
            break;
        default:
            break;
    }

    // Загрузка текстуры пули
    try{
        textureBull.loadFromFile("resourse/background/bullet.png");
    }catch (...){
        std::cout<<"Not found png"<<std::endl;
    }
    spriteBull.setTexture(textureBull);
}

// Обновление позиции и проверка столкновений
void Bullet::update(float time, int x1, int y1, int x2, int y2, Card &card) {
    x += dx * time; // Смена координат
    y += dy * time;
    spriteBull.setPosition(x, y);
    for (int i = y / 50; i < (y + h) / 50; i++) {
        for (int j = x / 50; j < (x + w) / 50; j++) {
            if (card.getItemCard(i, j) == 'X') {
                // Столкновение с препятствием: пуля умирает
                dx = 0;
                dy = 0;
                life = false;
            }
        }
    }

    // Попадение в первого игрока
    if (pl == 1) {
        if (x > x1 && y > y1 && x < (x1 + 100) && y < (y1 + 100)) {
            life = false;
            p1life = false;
        }
    }

    // Попадение во второго игрока
    if (pl == 2) {
        if (x > x2 && y > y2 && x < (x2 + 100) && y < (y2 + 100)) {
            life = false;
            p2life = false;
        }
    }
}

// Отрисовка пули
void Bullet::drawBullet(RenderWindow &window) {
    window.draw(spriteBull);
}
