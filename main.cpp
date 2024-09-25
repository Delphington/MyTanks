#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Config.cpp"
#include <string>

#include "Environment.h"
#include "Score.h"
#include "Player.h"
#include "GameMenu.h"
#include "CollisionUtils.h"
#include "Bullet.h"

using namespace std;
using namespace sf;

//#Объект пули
//#Размер поля 1600x900
//#Размер пули 15x15


//Отрисовка итога, кто выиграл, финальное окно
void gameOver(RenderWindow &window, Player &player1, Player &player2) {
    window.clear();
    bool flag = true;

    Texture texture;
    Sprite sprite;

    while (window.isOpen() && flag) {
        Event event2;
        while (window.pollEvent(event2)) {
            if (event2.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (player2.getScore() > player1.getScore()) {
            if (!texture.loadFromFile(
                    "D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p2won.png")) { ; // Обработка ошибки загрузки текстуры
            }
        } else {
            if (!texture.loadFromFile(
                    "D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p1won.png")) { ; // Обработка ошибки загрузки текстуры
            }
        }
        sprite.setTexture(texture);
        window.draw(sprite); // Отрисовка спрайта
        window.display();

        //выход на главное меню
        if (Keyboard::isKeyPressed(Keyboard::P)) {
            window.clear();
            flag = false;
        }
    }
}


// функция настройки текста
void InitText(Text &mtext, float xpos, float ypos, String str, int size_font = 60,
              Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

// Функция перехода к игре
void GamеStart(RenderWindow &window, Player &player1, Player &player2) {
    window.clear();

    Config config;


    std::list<Bullet *> bullets;
    std::list<Bullet *>::iterator it;

    Card card;


    //RenderWindow window(VideoMode(1600, 900), config.nameGame); // Игровое окно

    Font fonts;
    if (!fonts.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Arial.ttf")) {
        // Обработка ошибки загрузки шрифта
        cerr << "dont found font";
    }


//  ### Создание объектов счетов
    int position_1_x = 862;
    int position_1_y = 0;

    int position_2_x = 712;
    int position_2_y = 0;

    const unsigned int SIZE_OF_SCORE = 50;

    Score score1(fonts, SIZE_OF_SCORE, Color::Green, position_1_x, position_1_y); //Первый игрок, красный
    Score score2(fonts, SIZE_OF_SCORE, Color::Red, position_2_x, position_2_y); //Первый игрок, красный


    Environment backGround("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\ground.png");
    Environment wall("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\briq.png");

    bool endgame = false;

    Clock clock;

    int ws = 100;
    while (window.isOpen() && endgame == false) {
        //Возвращаем время, после вызова/создания объекта
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 500;

        Event event;


        //Обрабатывает события, пока события в window есть цикл идет
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); //Закрываем окно при нажатии на крестик
            } else if (event.type == Event::KeyPressed) {//обратботка клавиш
                //Стрельба первого танка
                if (event.key.code == Keyboard::V) {
                    bullets.push_back(new Bullet(player1.getSprite().getPosition().x + 43,
                                                 player1.getSprite().getPosition().y + 43, player1.getState(), 1));
                } else if (event.key.code == Keyboard::L) {
                    //стрельба второго танка
                    bullets.push_back(new Bullet(player2.getSprite().getPosition().x + 43,
                                                 player2.getSprite().getPosition().y + 43, player2.getState(), 2));
                }
            }
        }





        // Управление игрок 1
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (CollisionUtils::collXL(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player1.move(-0.1 * time, 0);
            }
            player1.setTextureRect(IntRect(301, 0, 100, 100));
            player1.setState(1); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (CollisionUtils::collXR(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player1.move(0.1 * time, 0);
            }
            player1.setTextureRect(IntRect(100, 0, 100, 100));
            player1.setState(2); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (CollisionUtils::collYU(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player1.move(0, -0.1 * time);
            }
            player1.setTextureRect(IntRect(0, 0, 100, 100));
            player1.setState(3); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (CollisionUtils::collYD(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player1.move(0, 0.1 * time);
            }
            player1.setTextureRect(IntRect(200, 0, 100, 100));
            player1.setState(4); //Направление
        }

        //--------------------------------------------------------------------------------------------------------

        // Управление игрок 2
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (CollisionUtils::collXL(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player2.move(-0.1 * time, 0);
            }
            player2.setTextureRect(IntRect(301, 0, 100, 100));         //текстура для анимации
            player2.setState(1); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (CollisionUtils::collXR(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player2.move(0.1 * time, 0);
            }
            player2.setTextureRect(IntRect(100, 0, 100, 100));
            player2.setState(2); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (CollisionUtils::collYU(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player2.move(0, -0.1 * time);
            }
            player2.setTextureRect(IntRect(0, 0, 100, 100));
            player2.setState(3); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (CollisionUtils::collYD(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player2.move(0, 0.1 * time);
            }
            player2.setTextureRect(IntRect(200, 0, 100, 100));
            player2.setState(4); //направление
        }
        //----------------------------------------------------



        //Закрытие программы через Escape
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }



        //#обновление состояния пуль в игре, а также проверку жизни игроков и пуль


        //#Обновление всех пуль лежащие в векторе
        for (it = bullets.begin(); it != bullets.end(); it++) {
            (*it)->update(time, player2.getSprite().getPosition().x, player2.getSprite().getPosition().y,
                          player1.getSprite().getPosition().x,
                          player1.getSprite().getPosition().y, card);
        }


        //#проверка Игрока 1
        for (it = bullets.begin(); it != bullets.end();) {
            Bullet *b = *it;
            if (b->p1life == false) {  //#Игрок умер
                player1.setScore(player1.getScore() + 1);
                if (player1.getScore() > 4) {
                    endgame = true;
                    //#закнчиваем игру
                }
                it = bullets.erase(it);   //#удаляем пулю из вектора
                player2.spriteSetPosition(1400, 400);
                player1.spriteSetPosition(100, 400);
                delete b;
            } else {
                it++;
            }
        }



        //#проверка игрока 2
        for (it = bullets.begin(); it != bullets.end();) {//Проверка жизни игрока 2
            Bullet *b = *it;
            if (b->p2life == false) {
                player2.setScore(player2.getScore() + 1);  //увеличение счета
                if (player2.getScore() > 4) {
                    endgame = true;
                }
                it = bullets.erase(it);
                player2.spriteSetPosition(1400, 400);
                player1.spriteSetPosition(100, 400);
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
        score1.setString(to_string(player2.getScore()));
        score2.setString(to_string(player1.getScore()));


        //#Очистка перед отрисовкой нового кадра
        window.clear();

        //# Отрисовка карты
        for (int i = 0; i < card.getHeight(); i++) {
            for (int j = 0; j < card.getWidth(); j++) {
                if (card.getItemCard(i, j) == 'X') {
                    wall.setPosition(j * 50, i * 50);
                    window.draw(wall.getRectangle());
                }
                if (card.getItemCard(i, j) == ' ') {
                    backGround.setPosition(j * 50, i * 50);
                    window.draw(backGround.getRectangle());
                }
            }
        }

//        //# Отрисовка пуль
        for (it = bullets.begin(); it != bullets.end(); it++) {
            (*it)->drawb(window);
        }

        //# Отрисовка игроков
        window.draw(player2.getSprite());
        window.draw(player1.getSprite());
        //#  отрисовка счета
        window.draw(score1.getScoreText());
        window.draw(score2.getScoreText());
        window.display(); //# Отображение
    }
    gameOver(window, player1, player2);
}

// Функция настройки игры
void Options() {}

// Функция с описанием игры
void About_Game() {

}

// функция настройки текста
void InitText(Text &mtext, float xpos, float ypos, String str, int size_font,
              Color menu_text_color, int bord, Color border_color) {
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}


int main() {
    Config config;
    //TODO: ------------------------------------
    Player player1(100, 400, 0);
    player1.setInitialization("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank2.png",
                              IntRect(100, 0, 100, 100));


    Player player2(1400, 400, 0); //Инициализация игрока который по клавишам
    player2.setInitialization("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank1.png",
                              IntRect(300, 0, 100, 100));

//TODO: ------------------------------------

// Создаём окно windows



    RenderWindow windows(VideoMode(1600, 900), config.nameGame); // Игровое окно


    // Устанавливаем фон для графического окна // Создаём прямоугольник
    RectangleShape background(Vector2f(config.SCREEN_WIGHT, config.SCREEN_HEIGHT));
    // Загружаем в прямоугольник текстуру с изображением menu9.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile(
            "D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Menu\\menu9.jpg")) {
        return 4;
    }
    background.setTexture(&texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Arial.ttf")) return 5;
    Text Titul;
    Titul.setFont(font);
    // Текст с названием игры
    // InitText(Titul, config.SCREEN_WIGHT/3, config.SCREEN_HEIGHT/10, config.nameGame, 150, Color(237, 147, 0), 3);

    // Название пунктов меню
    String name_menu[]{L"Старт", L"Настройки", L"О игре", L"Выход"};

    // Объект игровое меню
    game::GameMenu mymenu(windows, 950, 350, 4, name_menu, 100, 120);
    // Установка цвета элементов пунктов меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // выравнивание по центру пунктов меню
    mymenu.AlignMenu(2);

    while (windows.isOpen()) {
        Event event;
        while (windows.pollEvent(event)) {

            //закрытие через крестик
            if (event.type == Event::Closed) {
                windows.close();
            }

            //Закрытие программы через Escape
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                windows.close();
            }


            if (event.type == Event::KeyReleased) {
                // События выбра пунктов меню
                // нажати на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                // нажати на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                // нажати на клавиатуре клавиши Enter
                if (event.key.code == Keyboard::Return) {
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber()) {
                        case 0:
                            player1.setScore(0);
                            player2.setScore(0);
                            GamеStart(windows, player1, player2);
                            break;
                        case 1:
                            Options();
                            break;
                        case 2:
                            About_Game();
                            break;
                        case 3: //Выход
                            windows.close();
                            break;
                    }
                }
            }
        }

        // drawMainMenu(windows, background,Titul, mymenu);
        windows.clear();
        windows.draw(background);
        windows.draw(Titul);
        mymenu.draw();
        windows.display();
    }


//TODO: ------------------------------------------------------------
    return 0;
}