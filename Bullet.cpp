#include "Bullet.h"
#include "Card.h" // Включаем Card.h для работы с классом Card

// Конструктор
Bullet::Bullet(int X, int Y, int direction, int player) {
    x = X;
    y = Y;
    pl = player;

    // Определение направления
    if (direction == 1) {
        dx = -0.3; // Стрельба влево
        //     dy = 0;
    } else if (direction == 2) {
        dx = 0.3; // Стрельба вправо
        //   dy = 0;
    } else {
        dx = 0;
        //  dy = 0;
    }

    if (direction == 3) {
        dy = -0.3; // Стрельба вверх
        //   dx = 0;
    } else if (direction == 4) {
        dy = 0.3; // Стрельба вниз
        //   dx = 0;
    }

    w = h = 15;
    p1life = true;
    p2life = true;
    life = true;

    // Загрузка текстуры пули
    textureBull.loadFromFile("resourse/background/bullet.png");
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

    // Установка позиции пули

}

// Отрисовка пули
void Bullet::drawb(RenderWindow &window) {
    window.draw(spriteBull);
}
