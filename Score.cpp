#include "Score.h"

// Конструктор
Score::Score(const Font &font, unsigned int size, const Color &color, float x, float y) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(size);
    scoreText.setFillColor(color);
    scoreText.setPosition(x, y);
}

// Установка строки текста
void Score::setString(const string &str) {
    scoreText.setString(str);
}

// Установка позиции текста
void Score::setPosition(float x, float y) {
    scoreText.setPosition(x, y);
}

// Получение текста счета
const Text &Score::getScoreText() const {
    return scoreText;
}
