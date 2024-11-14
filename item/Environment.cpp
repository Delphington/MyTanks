#include "Environment.h"

// Конструктор
Environment::Environment(const std::string &pathOfFile) {
    ground.loadFromFile(pathOfFile);
    rectangle.setTexture(ground);
}

// Геттер для спрайта
const sf::Sprite &Environment::getRectangle() const {
    return rectangle;
}

// Метод для установки позиции спрайта
void Environment::setPosition(float x, float y) {
    rectangle.setPosition(x, y);
}
