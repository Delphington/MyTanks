#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Config.cpp"
#include <string>

#include "Environment.cpp"
#include "Score.cpp"
#include "Player.cpp"
#include "GameMenu.h"
#include "CollisionUtils.cpp"



using namespace std;
using namespace sf;

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
    void update(float time, int x1, int y1, int x2, int y2, Card &card) {
        x += dx * time; //#смена координат
        y += dy * time;


        for (int i = y / 50; i < (y + h) / 50; i++) {
            for (int j = x / 50; j < (x + w) / 50; j++) {
                if (card.getItemCard(i, j) == 'X') {
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








// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
              Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);

// Функция перехода к игре
void GameStart()
{
    RenderWindow Play(VideoMode::getDesktopMode(), L"Уровень 1", Style::Fullscreen);


    RectangleShape background_play(Vector2f(1920, 1080));

    Texture texture_play;
    if (!texture_play.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Menu\\menu4.jpg")) exit(1);
    background_play.setTexture(&texture_play);

    while (Play.isOpen())
    {
        Event event_play;
        while (Play.pollEvent(event_play))
        {
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) { Play.close(); }
            }
        }
        Play.clear();
        Play.draw(background_play);
        Play.display();
    }
}

// Функция настройки игры
void Options()
{
    RenderWindow Options(VideoMode::getDesktopMode(), L"Настройки", Style::Fullscreen);

    RectangleShape background_opt(Vector2f(1920, 1080));
    Texture texture_opt;
    if (!texture_opt.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Menu\\menu1.jpg")) exit(2);

    background_opt.setTexture(&texture_opt);
    while (Options.isOpen())
    {
        Event event_opt;
        while (Options.pollEvent(event_opt))
        {
            if (event_opt.type == Event::Closed) Options.close();
            if (event_opt.type == Event::KeyPressed)
            {
                if (event_opt.key.code == Keyboard::Escape) Options.close();
            }
        }
        Options.clear();
        Options.draw(background_opt);
        Options.display();
    }

}

// Функция с описанием игры
void About_Game()
{
    RenderWindow About(VideoMode::getDesktopMode(), L"О игре", Style::Fullscreen);
    RectangleShape background_ab(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    Texture texture_ab;
    if (!texture_ab.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Menu\\menu2.jpg")) exit(3);
    background_ab.setTexture(&texture_ab);

    while (About.isOpen())
    {
        Event event_play;
        while (About.pollEvent(event_play))
        {
            if (event_play.type == Event::Closed) About.close();
            if (event_play.type == Event::KeyPressed)
            {
                if (event_play.key.code == Keyboard::Escape) About.close();
            }
        }
        About.clear();
        About.draw(background_ab);
        About.display();
    }
}



// функция настройки текста
void InitText(Text& mtext, float xpos, float ypos, String str, int size_font,
              Color menu_text_color, int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}












int main() {

//---------------

    // Создаём окно windows
    RenderWindow introductoryWindow;
    // Параметры: размер окна установить согласно текущему разрешению экрана
    // название моя игра, развернуть графическое окно на весь размер экрана
    introductoryWindow.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);

    //отключаем видимость курсора
    introductoryWindow.setMouseCursorVisible(false);

    // получаем текущий размер экрана
    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    // Устанавливаем фон для графического окна
    // Создаём прямоугольник
    RectangleShape background(Vector2f(width, height));
    // Загружаем в прямоугольник текстуру с изображением menu9.jpg
    Texture texture_window;
    if (!texture_window.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Menu\\menu9.jpg")) return 4;
    background.setTexture(&texture_window);

    // Устанавливаем шрифт для названия игры
    Font font;
    if (!font.loadFromFile("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\Arial.ttf")) return 5;
    Text Titul;
    Titul.setFont(font);
    // Текст с названием игры
    InitText(Titul, 480, 50, L"Апокалипсис", 150, Color(237, 147, 0), 3);

    // Название пунктов меню
    String name_menu[]{ L"Старт",L"Настройки", L"О игре",L"Выход"};

    // Объект игровое меню
    game::GameMenu mymenu(introductoryWindow, 950, 350, 4, name_menu, 100, 120);
    // Установка цвета элементов пунктов меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // выравнивание по центру пунктов меню
    mymenu.AlignMenu(2);

    while (introductoryWindow.isOpen())
    {
        Event event;
        while (introductoryWindow.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                // События выбра пунктов меню
                // нажати на клавиатуре стрелки вверх
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }
                // нажати на клавиатуре стрелки вниз
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }
                // нажати на клавиатуре клавиши Enter
                if (event.key.code == Keyboard::Return)
                {
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber())
                    {
                        case 0:GameStart();   break;
                        case 1:Options();     break;
                        case 2:About_Game();  break;
                        case 3:introductoryWindow.close(); break;

                    }

                }
            }
        }

        introductoryWindow.clear();
        introductoryWindow.draw(background);
        introductoryWindow.draw(Titul);
        mymenu.draw();
        introductoryWindow.display();
    }



//-----------







































    std::list<Bullet *> bullets;
    std::list<Bullet *>::iterator it;

    Card card;


    Config config;
    RenderWindow window(VideoMode(1600, 900), config.nameGame); // Игровое окно

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


//TODO: ------------------------------------
    Player player1(100, 400, 0);
    player1.setInitialization("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank2.png",
                              IntRect(100, 0, 100, 100));


    Player player2(1400, 400, 0); //Инициализация игрока который по клавишам
    player2.setInitialization("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\tank1.png",
                              IntRect(300, 0, 100, 100));

//TODO: ------------------------------------

    Environment backGround("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\ground.png");
    Environment wall("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\background\\briq.png");


//    Окно для результата (Какой танк выиграл и тд)
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
            }else if (event.type == Event::KeyPressed) {//обратботка клавиш
                //Стрельба первого танка
                if (event.key.code == Keyboard::V) {
                    bullets.push_back(new Bullet(player1.getSprite().getPosition().x + 43,
                                                 player1.getSprite().getPosition().y + 43, player1.getState(),1));
                }else if (event.key.code == Keyboard::L) {
                    //стрельба второго танка
                    bullets.push_back(new Bullet(player2.getSprite().getPosition().x + 43,
                                                 player2.getSprite().getPosition().y + 43, player2.getState(),2));
                }
            }
        }





        // Управление игрок 1
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (CollisionUtils::collXL(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,card) == 0) {
                player1.move(-0.1 * time, 0);
            }
            player1.setTextureRect(IntRect(301, 0, 100, 100));
            player1.setState(1); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (CollisionUtils::collXR(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y, ws,card) == 0) {
                player1.move(0.1 * time, 0);
            }
            player1.setTextureRect(IntRect(100, 0, 100, 100));
            player1.setState(2); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (CollisionUtils::collYU(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y,ws, card) == 0) {
                player1.move(0, -0.1 * time);
            }
            player1.setTextureRect(IntRect(0, 0, 100, 100));
            player1.setState(3); //Направление

        } else if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (CollisionUtils::collYD(player1.getSprite().getPosition().x,player1.getSprite().getPosition().y, ws, card) == 0) {
                player1.move(0, 0.1 * time);
            }
            player1.setTextureRect(IntRect(200, 0, 100, 100));
            player1.setState(4); //Направление
        }

        //--------------------------------------------------------------------------------------------------------

        // Управление игрок 2
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (CollisionUtils::collXL(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,card) == 0) {
                player2.move(-0.1 * time, 0);
            }
            player2.setTextureRect(IntRect(301, 0, 100, 100));         //текстура для анимации
            player2.setState(1); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (CollisionUtils::collXR(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y, ws,card) == 0) {
                player2.move(0.1 * time, 0);
            }
            player2.setTextureRect(IntRect(100, 0, 100, 100));
            player2.setState(2); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (CollisionUtils::collYU(player2.getSprite().getPosition().x, player2.getSprite().getPosition().y,ws, card) == 0) {
                player2.move(0, -0.1 * time);
            }
            player2.setTextureRect(IntRect(0, 0, 100, 100));
            player2.setState(3); //направление

        } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (CollisionUtils::collYD(player2.getSprite().getPosition().x,player2.getSprite().getPosition().y, ws, card) == 0) {
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

        if (player2.getScore() > player1.getScore()) {
            // window2.draw("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p1won.png");
        } else {
            // window2.draw("D:\\_DELPGINGTON\\University\\Sem_3\\course\\MyTanks\\resourse\\p2won.png");
        }
        window2.display();
    }
    return 0;

}