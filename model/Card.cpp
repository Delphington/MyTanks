#include "Card.h"

// Инициализация карты
void Card::setInitialization() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                //установка счета
                if ((i == 0 && j == 14) || (i == 0 && j == 17)) {
                    card[i][j] = '0';
                } else {
                    //установка идентификатора стены
                    card[i][j] = 'X';
                }
            } else {
                card[i][j] = ' ';
            }
        }
    }
}

// Конструктор
Card::Card() {
    setInitialization(); // Инициализация при создании объекта
}

const int Card::getHeight() {
    return HEIGHT;
}

const int Card::getWidth() {
    return WIDTH;
}

// Получение элемента карты
char Card::getItemCard(int i, int j) {
    if ((i >= 0 && i < HEIGHT) && (j >= 0 && j < WIDTH)) {
        return card[i][j];
    }
    return '\0'; // Возвращаем нулевой символ в случае ошибки
}

// Установка элемента карты
void Card::setItemCard(int i, int j, char value) {
    if ((i >= 0 && i < HEIGHT) && (j >= 0 && j < WIDTH)) {
        card[i][j] = value;
    }
}