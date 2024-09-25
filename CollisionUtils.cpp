#include "CollisionUtils.h"

// Коллизия при движении влево по OX
bool CollisionUtils::collXL(int dx, int dy, int w, Card& card) {
    for (int i = dy / CELL_SIZE; i < (dy + w) / CELL_SIZE && i < card.getHeight(); i++) {
        if (card.getItemCard(i, dx / CELL_SIZE) == 'X') {
            return true;
        }

        if (i + 1 < card.getHeight() && card.getItemCard(i + 1, dx / CELL_SIZE) == 'X') {
            return true;
        }
        if (i + 2 < card.getHeight() && card.getItemCard(i + 2, dx / CELL_SIZE) == 'X') {
            return true;
        }
    }
    return false; // Если ничего не найдено
}

// Коллизия при движении вправо по OX
bool CollisionUtils::collXR(int dx, int dy, int w, Card& card) {
    for (int i = dy / CELL_SIZE; i < (dy + w) / CELL_SIZE && i < card.getHeight(); i++) {
        if (card.getItemCard(i, (dx + w) / CELL_SIZE) == 'X') {
            return true;
        }

        if (i + 1 < card.getHeight() && card.getItemCard(i + 1, (dx + w) / CELL_SIZE) == 'X') {
            return true;
        }
        if (i + 2 < card.getHeight() && card.getItemCard(i + 2, (dx + w) / CELL_SIZE) == 'X') {
            return true;
        }
    }
    return false; // Если ничего не найдено
}

// Коллизия при движении вверх по OY
bool CollisionUtils::collYU(int dx, int dy, int w, Card& card) {
    for (int j = (dx + 1) / CELL_SIZE; j < (dx + w) / CELL_SIZE; j++) {
        // Проверяем границы массива
        if (dy / CELL_SIZE > 0 && dy / CELL_SIZE < card.getHeight()) {
            if (card.getItemCard(dy / CELL_SIZE - 1, j) == 'X') {
                return true;
            }

            if (j + 1 < card.getWidth() && card.getItemCard(dy / CELL_SIZE - 1, j + 1) == 'X') {
                return true;
            }
            if (j + 2 < card.getWidth() && card.getItemCard(dy / CELL_SIZE - 1, j + 2) == 'X') {
                return true;
            }
        }
    }
    return false; // Если ничего не найдено
}

// Коллизия при движении вниз по OY
bool CollisionUtils::collYD(int dx, int dy, int w, Card& card) {
    for (int j = (dx + 1) / CELL_SIZE; j < (dx + w) / CELL_SIZE; j++) {
        // Проверяем границы массива и наличие 'X' в нужной позиции
        if ((dy + 100) / CELL_SIZE < card.getHeight()) {
            if (card.getItemCard((dy + 100) / CELL_SIZE, j) == 'X') {
                return true;
            }

            if (j + 1 < card.getWidth() && card.getItemCard((dy + 100) / CELL_SIZE, j + 1) == 'X') {
                return true;
            }
            if (j + 2 < card.getWidth() && card.getItemCard((dy + 100) / CELL_SIZE, j + 2) == 'X') {
                return true;
            }
        }
    }
    return false; // Если ничего не найдено
}
