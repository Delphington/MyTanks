#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
private:
    float x, y;
    int score, state;
    Texture texture;
    Sprite sprite;

public:
    Player(float x, float y, int score) : x(x), y(y), score(score) {}

    void setInitialization(String pathOfPicture, IntRect rect) {
        texture.loadFromFile(pathOfPicture);
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(x, y);
    }

    int getScore() const { return score; }

    int getState() const { return state; }

    void setState(int state) {
        this->state = state;
    }

    const Sprite &getSprite() const { return sprite; }

    void setScore(int score) { this->score = score; }

    // Метод для перемещения спрайта
    void move(float dx, float dy) {
        sprite.move(dx, dy);
//
//        x += dx; // Обновляем координаты игрока
//        y += dy;
    }

    void spriteSetPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // Метод для изменения текстурного прямоугольника
    void setTextureRect(IntRect rect) {
        sprite.setTextureRect(rect);
    }
};