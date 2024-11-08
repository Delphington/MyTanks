#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Config.cpp"
#include <string>
#include<vector>
#include "Environment.h"
#include "Score.h"
#include "Player.h"
#include "GameMenu.h"
#include "CollisionUtils.h"
#include "Bullet.h"
#include"redactor.h"

using namespace std;
using namespace sf;

//#Объект пули
//#Размер поля 1600x900
//#Размер пули 15x15
Redactor red;

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
                    "resourse/p2won.png")) { ; // Обработка ошибки загрузки текстуры
            }
        } else {
            if (!texture.loadFromFile(
                    "resourse/p1won.png")) { ; // Обработка ошибки загрузки текстуры
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


    std::vector<Bullet *> bullets;
    std::vector<Bullet *>::iterator it;

    Card card;
    if(red.get_y() == 1)
        card = red.get_Card();

    //RenderWindow window(VideoMode(1600, 900), config.nameGame); // Игровое окно

    Font fonts;
    if (!fonts.loadFromFile("resourse/Arial.ttf")) {
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


    Environment backGround("resourse/background/ground.png");
    Environment wall("resourse/background/briq.png");
    player1.setState(2);
    player2.setState(1);
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


        for (it = bullets.begin(); it != bullets.end(); it++) {
            (*it)->update(time, player2.getSprite().getPosition().x, player2.getSprite().getPosition().y,
                          player1.getSprite().getPosition().x,
                          player1.getSprite().getPosition().y, card);
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

        }else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (CollisionUtils::collXR(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {

                player2.move(0.1 * time, 0);
            }
            player2.setTextureRect(IntRect(100, 0, 100, 100));
            player2.setState(2); //направление

        }else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (CollisionUtils::collYU(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,
                                       card) == 0) {
                player2.move(0, -0.1 * time);
            }
            player2.setTextureRect(IntRect(0, 0, 100, 100));
            player2.setState(3); //направление

        }else if (Keyboard::isKeyPressed(Keyboard::Down)) {
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
                bullets.clear();
                delete b;
                break;
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
                bullets.clear();
                break;
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
void Options() {
    Config config;
    RenderWindow window(VideoMode(1600, 900), config.nameGame);
    Environment backGround("resourse/background/ground.png");
    Environment wall("resourse/background/briq.png");
    Card card = red.get_Card();
    Font font;
    if (!font.loadFromFile("resourse/Arial.ttf")) return;
    sf::Text sr("save", font);
    sr.setPosition(0,0);
    sr.setFillColor(sf::Color::Black);
    sf::RectangleShape but(sf::Vector2f(0,0));
    but.setSize(sf::Vector2f(100,50));
    bool flag = false;
    while(window.isOpen()){
        Event event;
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    Vector2i pos;
                    pos = Mouse::getPosition(window);
                    if(card.getItemCard(pos.y/50, pos.x/50) == ' ')card.setItemCard(pos.y/50,pos.x/50, 'X');
                    else if(card.getItemCard(pos.y/50, pos.x/50) == 'X' && pos.y/50 != 0 && pos.x/50 != 0) card.setItemCard(pos.y/50, pos.x/50, ' ');
                }if(but.getGlobalBounds().contains(mouse.x, mouse.y)){
                    flag = true;
                    window.close();
                }
            }
        }
        window.clear();
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
        window.draw(but);
        window.draw(sr);
        window.display();
    }
    if(flag) red.setCard(card);
    for(int i = 0;i < 18;i++){
        for(int j = 0;j < 32;j++)
            std::cout << card.getItemCard(i,j);
        std::cout << "\n";
    }

}

// Функция с описанием игры
void About_Game(RenderWindow &window, Player &player1, Player &player2) {
    std::cout << "AAAAA\n";
    window.clear();
    Font font;
    if (!font.loadFromFile("resourse/Arial.ttf")) return ;
    Text Titul;
    Titul.setFont(font);
    Texture textr;
    textr.loadFromFile("213.png");
    Sprite sprt;
    sprt.setTexture(textr);
    int flag = 0;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                flag = 1;
            }
        }
        if(flag) break;
        window.clear();
        window.draw(sprt);
        window.display();
    }

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
    player1.setInitialization("resourse/tank2.png",
                              IntRect(100, 0, 100, 100));


    Player player2(1300, 400, 0); //Инициализация игрока который по клавишам
    player2.setInitialization("resourse/tank1.png",
                              IntRect(300, 0, 100, 100));

//TODO: ------------------------------------

// Создаём окно windows



    RenderWindow windows(VideoMode(1600, 900), config.nameGame); // Игровое окно


    // Устанавливаем фон для графического окна // Создаём прямоугольник
    RectangleShape background(Vector2f(config.SCREEN_WIGHT, config.SCREEN_HEIGHT));
    // Загружаем в прямоугольник текстуру с изображением menu9.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile(
            "resourse/Menu/menu9.png")) {
        return 4;
    }
    background.setTexture(&texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("resourse/Arial.ttf")) return 5;
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
                            About_Game(windows, player1, player2);
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