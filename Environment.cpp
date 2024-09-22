
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Environment {
private:
    Texture ground;
    Sprite rectangle;

public:
    Environment(const string &pythOfFile) {
        ground.loadFromFile(pythOfFile);
        rectangle.setTexture(ground);
    }

    const Sprite &getRectangle() const {
        return rectangle;
    }

    void setPosition(float x, float y) {
        rectangle.setPosition(x, y);
    }
};