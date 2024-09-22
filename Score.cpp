
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
    Score(const Font &font, unsigned int size, const Color &color, float x, float y) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(size);
        scoreText.setFillColor(color);
        scoreText.setPosition(x, y);
    }

    void setString(const string &str) {
        scoreText.setString(str);
    }

    void setPosition(float x, float y) {
        scoreText.setPosition(x, y);
    }

    const Text &getScoreText() const {
        return scoreText;
    }
};
