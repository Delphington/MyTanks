#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Score {
private:
    Text scoreText;
    Font font;
    float x, y;

public:
    // Конструктор
    Score(const Font &font, unsigned int size, const Color &color, float x, float y);

    // Установка строки текста
    void setString(const string &str);

    // Установка позиции текста
    void setPosition(float x, float y);

    // Получение текста счета
    const Text &getScoreText() const;
};
