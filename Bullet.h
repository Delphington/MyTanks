#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Card; // Предварительное объявление класса Card

class Bullet {
public:
    float x, y; // Начальные координаты
    float dx, dy; // Скорость движения
    float w, h; // Размеры пули
    float pl; // Уникальный идентификатор игрока
    bool life; // Жива ли пуля
    bool p1life, p2life; // Жизни игроков

    Texture textureBull;
    Sprite spriteBull;

    Bullet(int X, int Y, int direction, int player); // Конструктор

    void update(float time, int x1, int y1, int x2, int y2, Card &card); // Обновление позиции и проверка столкновений
    void drawb(RenderWindow &window); // Отрисовка пули
};