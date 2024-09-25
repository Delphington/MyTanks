#pragma once


#include <SFML/Graphics.hpp>

class Player {
private:
    float x, y;             // Позиция игрока
    int score;              // Очки игрока
    int state;              // Состояние игрока
    sf::Texture texture;    // Текстура игрока
    sf::Sprite sprite;      // Спрайт игрока

public:
    // Конструктор
    Player(float x, float y, int score);

    // Метод для инициализации текстуры и спрайта
    void setInitialization(const std::string& pathOfPicture, const sf::IntRect& rect);

    int getScore() const;
    int getState() const;
    void setState(int state);
    const sf::Sprite& getSprite() const;
    void setScore(int score);

    // Метод для перемещения спрайта
    void move(float dx, float dy);

    // Метод для установки позиции спрайта
    void spriteSetPosition(float x, float y);

    // Метод для изменения текстурного прямоугольника
    void setTextureRect(const sf::IntRect& rect);
};

