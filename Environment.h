#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Environment {
private:
    sf::Texture ground;     // Текстура земли
    sf::Sprite rectangle;   // Спрайт для отображения

public:
    // Конструктор
    Environment(const std::string &pathOfFile);

    // Геттер для спрайта
    const sf::Sprite &getRectangle() const;

    // Метод для установки позиции спрайта
    void setPosition(float x, float y);
};