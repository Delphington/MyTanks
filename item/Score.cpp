#include "Score.h"

// Конструктор
Score::Score(const Font &font, unsigned int size, const Color &color, float x, float y) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(size);
    scoreText.setFillColor(color);
    scoreText.setPosition(x, y);
}

// Установка строки текста
void Score::setScoreText(const string &str) {
    scoreText.setString(str);
}

// Получение текста счета
const Text &Score::getScoreText() const {
    return scoreText;
}
