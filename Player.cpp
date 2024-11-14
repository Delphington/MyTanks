#include "Player.h"

using namespace std;
using namespace sf;


// Конструктор
Player::Player(float x, float y, int score) : x(x), y(y), score(score) {}

// Метод для инициализации текстуры и спрайта
void Player::setInitialization(const std::string& pathOfPicture, const sf::IntRect& rect) {
    texture.loadFromFile(pathOfPicture);
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setPosition(x, y);
}

// Геттеры и сеттеры
int Player::getScore() const {
    return score;
}

int Player::getState() const {
    return state;
}

void Player::setState(int state) {
    this->state = state;
}

const sf::Sprite& Player::getSprite() const {
    return sprite;
}

void Player::setScore(int score) {
    this->score = score;
}

// Метод для перемещения спрайта
void Player::move(float dx, float dy) {
    sprite.move(dx, dy);
}

// Метод для установки позиции спрайта
void Player::spriteSetPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Метод для изменения текстурного прямоугольника
void Player::setTextureRect(const sf::IntRect& rect) {
    sprite.setTextureRect(rect);
}