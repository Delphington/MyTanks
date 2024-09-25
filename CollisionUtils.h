#pragma once

#include "Card.h" // Предполагается, что класс Card определён в этом файле

class CollisionUtils {
public:
    // Размер клетки
    static const int CELL_SIZE = 50;

    // Коллизия при движении влево по OX
    static bool collXL(int dx, int dy, int w, Card& card);

    // Коллизия при движении вправо по OX
    static bool collXR(int dx, int dy, int w, Card& card);

    // Коллизия при движении вверх по OY
    static bool collYU(int dx, int dy, int w, Card& card);

    // Коллизия при движении вниз по OY
    static bool collYD(int dx, int dy, int w, Card& card);
};


