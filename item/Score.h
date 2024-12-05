#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Score {
private:
    Text scoreText;
    Font font;
    int x, y;

public:
    // Конструктор
    Score(const Font &font, unsigned int size, const Color &color, float x, float y);

    // Установка строки текста
    void setScoreText(const string &str);

    // Получение текста счета
    const Text &getScoreText() const;
};
