#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>


#include "Config.cpp"

using namespace sf;

//карты с координтами
const int H = 18;
const int W = 32;

String TileMap[H] = {
        "BBBBBBBBBBBBBB0BB0BBBBBBBBBBBBBB",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "B                              B",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};


String TileMaps[H] = {
        "BBBBBBBBBBBBBB0BB0BBBBBBBBBBBBBB",
        "B    B                  B      B",
        "B    B                  B      B",
        "B    B                         B",
        "B              B               B",
        "B              B               B",
        "B        B     B   BBBB        B",
        "B        B            B        B",
        "B        B            B        B",
        "B        B            B        B",
        "B        B            B        B",
        "B        BBBB    B    B        B",
        "B                B             B",
        "B                B             B",
        "B                         B    B",
        "B      B                  B    B",
        "B      B                  B    B",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};


/////////////////////////////////////////////// players collision
//# 50 - размер клетки
//# Коллиция при движении влево по OX
bool collXL(int dx, int dy, int w) {
    for (int i = (dy + 1) / 50; i < (dy + w - 2) / 50; i++) {
        if (TileMap[i][dx / 50] == 'B') {
            return 1;
        } else {
            if (TileMap[i + 1][dx / 50] == 'B') {
                return 1;
            } else {
                if (TileMap[i + 2][dx / 50] == 'B') {
                    return 1;
                }
                return 0;
            }
        }
    }
}

//# 50 - размер клетки
//# Коллиция при движении вправо по OX
bool collXR(int dx, int dy, int w) {
    for (int i = (dy + 1) / 50; i < (dy + w - 2) / 50; i++) {
        if (TileMap[i][(dx + 100) / 50] == 'B') {
            return 1;
        } else {
            if (TileMap[i + 1][(dx + 100) / 50] == 'B') {
                return 1;
            } else {
                if (TileMap[i + 2][(dx + 100) / 50] == 'B') {
                    return 1;
                }
                return 0;
            }
        }
    }
}

//# 50 - размер клетки
//# Коллиция при движении вверх OY

bool collYU(int dx, int dy, int w) {
    for (int j = (dx + 1) / 50; j < (dx + w) / 50; j++) {
        if (TileMap[dy / 50][j] == 'B') {
            return 1;
        } else {
            if (TileMap[dy / 50][j + 1] == 'B') {
                return 1;
            } else {
                if (TileMap[dy / 50][j + 2] == 'B') {
                    return 1;
                }
                return 0;
            }
        }
    }
}

bool collYD(int dx, int dy, int w) {
    for (int j = (dx + 1) / 50; j < (dx + w) / 50; j++) {
        if (TileMap[(dy + 100) / 50][j] == 'B') {
            return 1;
        } else {
            if (TileMap[(dy + 100) / 50][j + 1] == 'B') {
                return 1;
            } else {
                if (TileMap[(dy + 100) / 50][j + 2] == 'B') {
                    return 1;
                }
                return 0;
            }
        }
    }
    //нет явного выброса
}

/////////////////////////////////////////////// pkayers collision
/////////////////////////////////////////////// Bullets

//#Объект пули
//#Размер поля 1600x900
//#Размер пули 15x15
class Bullet {
public:
    float x, y; //#Начальные координаты
    float dx, dy; //#скорость движения
    float w, h; //#размеры пули
    float pl; //# Ундификатор игрока
    bool life;  //# Жива ли сама пуля
    bool p1life, p2life;  //# жизни игроков

    Texture textureBull;
    Sprite spriteBull;

    Bullet(int X, int Y, int direction, int player) {
        x = X;
        y = Y;
        pl = player;
        //#direction -   направление
        if (direction == 1) {
            dx = -0.3;  //#Стрельба влево
        } else if (direction == 2) {
            dx = 0.3;  //#Стрельба вправо
        } else {
            dx = 0;
        }

        if (direction == 3) {
            dy = -0.3;  //#стрельба вверх
        } else if (direction == 4) {
            dy = 0.3;  //#Стрельба вниз
        } else {
            dy = 0;
        }

        w = h = 15;
        p1life = true;
        p2life = true;
        life = true;
        textureBull.loadFromFile(
                "D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\bullet.png");
        spriteBull.setTexture(textureBull);
    }

    //#Обновлении позиции опираясь на время и проверка столкновения
    void update(float time, int x1, int y1, int x2, int y2) {
        x += dx * time; //#смена координат
        y += dy * time;


        for (int i = y / 50; i < (y + h) / 50; i++) {
            for (int j = x / 50; j < (x + w) / 50; j++) {
                if (TileMap[i][j] == 'B') {
                    //Столкновение с припятствием пуля умирает
                    dx = 0;
                    dy = 0;
                    life = false;
                }
            }
        }

        //#попадение в первого игрока
        if (pl == 1) {
            if (x > x1 && y > y1 && x < (x1 + 100) && y < (y1 + 100)) {
                life = false;
                p1life = false;
            }
        }

        //#второй игрок
        if (pl == 2)
            if (x > x2 && y > y2 && x < (x2 + 100) && y < (y2 + 100)) {
                life = false;
                p2life = false;
            }

        //установка позиции пули
        spriteBull.setPosition(x, y);

    }

    void drawb(RenderWindow &window) {
        window.draw(spriteBull);
    }
};


int main() {
    std::list<Bullet *> bullets;
    std::list<Bullet *>::iterator it;

    Config config;
    RenderWindow window(VideoMode(1600, 900), config.nameGame); // Игровое окно


    Font font;
    if (!font.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Arial.ttf")) {
        // Обработка ошибки загрузки шрифта
        return -1;
    }


//Установка счета
    Text scoreText;
    Text scoreText1;
    scoreText.setFont(font);
    scoreText1.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText1.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Green);
    scoreText1.setFillColor(sf::Color::Red);
//------------------

//Инцилизация позиций и вида танчиков
    Texture t;
    t.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank1.png");
    Sprite s;
    s.setTexture(t);
    s.setTextureRect(IntRect(300, 0, 100, 100));
    s.setPosition(1400, 400);                        // начальная позиция второго игрока

    Texture t2;
    t2.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank2.png"); // сама текстура
    Sprite s2;
    s2.setTexture(t2);   //установка текстуры
    s2.setTextureRect(IntRect(100, 0, 100, 100));  //размер
    s2.setPosition(100, 400);                       // начальная позиция первого игрока

    //--------------------------------------
    //Окружение
    //коричнивая стена
    Texture wall;
    wall.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\briq.png");
    Sprite rectangle;
    rectangle.setTexture(wall);


    //установка серого бэекграунда
    Texture ground;
    ground.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\ground.png");
    Sprite rectangle2;
    rectangle2.setTexture(ground);



    //Окно для результата (Какой танк выиграл и тд)
//    Texture tp1won;
//    tp1won.loadFromFile("p1won.png");
//    Sprite sp1won;
//    sp1won.setTexture(tp1won);
//    sp1won.setPosition(0, 0);
//    Texture tp2won;
//    tp2won.loadFromFile("p2won.png");
//    Sprite sp2won;
//    sp2won.setTexture(tp2won);
//    sp2won.setPosition(0, 0);


    int state1 = 1;  //направление
    int state2 = 2;
    bool endgame = false;
    int p1score = 0;   //Счет игроков
    int p2score = 0;

    Clock clock;

    int ws = 100;
    while (window.isOpen() && endgame == false) {
        //Возвращаем время, после вызова/создания объекта
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;

        Event event;


        //Обрабатывает события, пока события в window есть цикл идет
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); //Закрываем окно при нажатии на крестик
            }
            //обратботка клавиш
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::L) {
                    //стрельба справа
                    bullets.push_back(new Bullet(s.getPosition().x + 43,
                                                 s.getPosition().y + 43, state1,
                                                 2));  /////// Стрельба игрок 2

//                    Если была нажата клавиша L,
//                    создается новый объект Bullet (пуля) с координатами,
//                    основанными на позиции объекта s (вероятно, это игрок 2).
//                    Позиция пули смещена на 43 пикселя по X и Y.
//                    Параметры state1 и 2 могут указывать состояние
//                    пули и игрока соответственно. Пуля добавляется в вектор bullets.

                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::V) {
                    bullets.push_back(new Bullet(s2.getPosition().x + 43,
                                                 s2.getPosition().y + 43, state2,
                                                 1));/////// Стрельба игрок 1
                }
            }

        }


        /////////////////////////////////////////////// Управление игрок 2
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (collXL(s.getPosition().x, s.getPosition().y, ws) == 0) {
                s.move(-0.1 * time, 0);  //0 -коллиций нет
            }
            //текстура для анимации
            s.setTextureRect(IntRect(301, 0, 100, 100));
            state1 = 1; //направление
        } else {
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (collXR(s.getPosition().x, s.getPosition().y, ws) == 0) {
                    s.move(0.1 * time, 0);
                }
                s.setTextureRect(IntRect(100, 0, 100, 100));
                state1 = 2;
            } else {
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    if (collYU(s.getPosition().x, s.getPosition().y, ws) == 0) {
                        s.move(0, -0.1 * time);
                    }
                    s.setTextureRect(IntRect(0, 0, 100, 100));
                    state1 = 3;
                } else {
                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        if (collYD(s.getPosition().x, s.getPosition().y, ws) == 0) {
                            s.move(0, 0.1 * time);
                        }
                        s.setTextureRect(IntRect(200, 0, 100, 100));
                        state1 = 4;
                    }
                }
            }
        }
        /////////////////////////////////////////////// Управление игрок 1
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (collXL(s2.getPosition().x, s2.getPosition().y, ws) == 0) {
                s2.move(-0.1 * time, 0);
            }
            s2.setTextureRect(IntRect(301, 0, 100, 100));
            state2 = 1;
        } else {
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                if (collXR(s2.getPosition().x, s2.getPosition().y, ws) == 0) {
                    s2.move(0.1 * time, 0);
                }
                s2.setTextureRect(IntRect(100, 0, 100, 100));
                state2 = 2;
            } else {
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    if (collYU(s2.getPosition().x, s2.getPosition().y, ws) == 0) {
                        s2.move(0, -0.1 * time);
                    }
                    s2.setTextureRect(IntRect(0, 0, 100, 100));
                    state2 = 3;
                } else {
                    if (Keyboard::isKeyPressed(Keyboard::S)) {
                        if (collYD(s2.getPosition().x, s2.getPosition().y, ws) == 0) {
                            s2.move(0, 0.1 * time);
                        }
                        s2.setTextureRect(IntRect(200, 0, 100, 100));
                        state2 = 4;
                    }
                }
            }
        }



        //Закрытие программы через Escape
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }



        //#обновление состояния пуль в игре, а также проверку жизни игроков и пуль


        //#Обновление всех пуль лежащие в векторе
        for (it = bullets.begin(); it != bullets.end(); it++){
            (*it)->update(time, s.getPosition().x, s.getPosition().y, s2.getPosition().x,
                          s2.getPosition().y);
        }


        //#проверка Игрока 1
        for (it = bullets.begin(); it != bullets.end();) {
            Bullet *b = *it;
            if (b->p1life == false) {  //#Игрок умер
                p2score++;
                if (p2score > 4) {
                    endgame = true;
                    //#закнчиваем игру
                }
                it = bullets.erase(it);   //#удаляем пулю из вектора
                s.setPosition(1400, 400);                 //возвращение на позиции после смерти
                s2.setPosition(100, 400);
                delete b;
            } else{
                it++;
            }

        }



        //#проверка игрока 2
        for (it = bullets.begin(); it != bullets.end();) {//Проверка жизни игрока 2
            Bullet *b = *it;
            if (b->p2life == false) {
                p1score++;
                if (p1score > 4){
                    endgame = true;
                }
                it = bullets.erase(it);
                s.setPosition(1400, 400);
                s2.setPosition(100, 400);
                delete b;
            } else it++;
        }


        //#Проверка пуль живы ли они
        for (it = bullets.begin(); it != bullets.end();) {
            Bullet *b = *it;
            if (b->life == false) {
                it = bullets.erase(it);
                delete b;
            } else it++;
        }



        //#изменение счета
        std::string scoreString = std::to_string(p1score);
        std::string scoreString1 = std::to_string(p2score);
        scoreText.setString(scoreString);
        scoreText1.setString(scoreString1);
        scoreText.setPosition(862, 0);
        scoreText1.setPosition(712, 0);


        //#Очистка перед отрисовкой нового кадра
        window.clear();

        //# Отрисовка карты
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') {
                    rectangle.setPosition(j * 50, i * 50);
                    window.draw(rectangle);
                }
                if (TileMap[i][j] == ' ') {
                    rectangle2.setPosition(j * 50, i * 50);
                    window.draw(rectangle2);
                }
            }
        }

//        //# Отрисовка пуль
//        for (it = bullets.begin(); it != bullets.end(); it++) {
//            (*it)->drawb(window);
//        }


        //# Отрисовка игроков
        window.draw(s);
        window.draw(s2);
        //#  отрисовка счета
        window.draw(scoreText);
        window.draw(scoreText1);
        window.display(); //# Отображение
    }
//




    //####################################################################################################################
    //Финальное окно
    window.close();
    RenderWindow window2(VideoMode(1600, 900), "Results!");
    while (window2.isOpen()) {
        Event event2;
        while (window2.pollEvent(event2)) {
            if (event2.type == Event::Closed)
                window2.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window2.close();
        window2.clear();

        if (p1score > p2score) {
           // window2.draw("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p1won.png");
        }else {
           // window2.draw("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p2won.png");
        }
        window2.display();
    }



    return 0;
}