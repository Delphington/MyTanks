#pragma once

class Card {
private:
    static const int HEIGHT = 18;
    static const int WIDTH = 32;
    char card[HEIGHT][WIDTH];

    void setInitialization();

public:
    Card(); // Конструктор

    static const int getHeight(); // Получение высоты
    static const int getWidth(); // Получение ширины

    char getItemCard(int i, int j); // Получение элемента карты
    void setItemCard(int i, int j, char value); // Установка элемента карты
};