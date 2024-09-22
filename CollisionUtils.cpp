#include "Card.cpp"


class CollisionUtils {
public:
    // Размер клетки
    static const int CELL_SIZE = 50;

    // Коллизия при движении влево по OX
    static bool collXL(int dx, int dy, int w, Card& card) {
        for (int i = dy / CELL_SIZE; i < (dy + w) / CELL_SIZE && i < card.getHeight(); i++) {
            if (card.getItemCard(i,dx / CELL_SIZE) ==  'X' ){
                return true;
            }

            if (i + 1 < card.getHeight() && card.getItemCard(i+1, dx / CELL_SIZE) == 'X') {
                return true;
            }
            if (i + 2 < card.getHeight() &&  card.getItemCard(i+2, dx / CELL_SIZE) == 'X') {
                return true;
            }
        }
        return false; // Если ничего не найдено
    }

    // Коллизия при движении вправо по OX
    static bool collXR(int dx, int dy, int w, Card& card) {
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


    // Коллиция при движении вверх OY
    static bool collYU(int dx, int dy, int w, Card& card) {
        for (int j = (dx + 1) / CELL_SIZE; j < (dx + w) / CELL_SIZE; j++) {
            // Проверяем, что мы не выходим за границы массива
            if (dy / CELL_SIZE > 0 && dy / CELL_SIZE < card.getHeight()) {
                if (card.getItemCard(dy / CELL_SIZE - 1,j) == 'X') {
                    return true;
                }

                if (j + 1 < card.getWidth() &&  card.getItemCard(dy / CELL_SIZE - 1 ,j+1)== 'X') {
                    return true;
                }
                if (j + 2 < card.getWidth() && card.getItemCard(dy / CELL_SIZE - 1 ,j+2) == 'X') {
                    return true;
                }
            }
        }
        return false; // Если ничего не найдено
    }

    // Коллиция при движении вниз OY
    static bool collYD(int dx, int dy, int w, Card& card) {
        for (int j = (dx + 1) / CELL_SIZE; j < (dx + w) / CELL_SIZE; j++) {
            // Проверяем границы массива и наличие 'X' в нужной позиции
            if ((dy + 100) / CELL_SIZE < card.getHeight()) {
                if (card.getItemCard((dy + 100) / CELL_SIZE, j) == 'X') {
                    return true;
                }

                if (j + 1 < 32 && card.getItemCard((dy + 100) / CELL_SIZE, j+1) == 'X') {
                    return true;
                }
                if (j + 2 < 32 && card.getItemCard((dy + 100) / CELL_SIZE, j+2) == 'X') {
                    return true;
                }
            }
        }
        return false; // Если ничего не найдено
    }
};