#pragma once

#include <SFML/Graphics.hpp>

namespace game {
    class GameMenu {
        float menuX;                   // Координаты меню по X
        float menuY;                   // Координаты меню по Y
        int menuStep;                  // Расстояние между пунктами меню
        int maxMenu;                   // Максимальное количество пунктов меню
        int sizeFont;                  // Размер шрифта
        int mainMenuSelected;           // Номер текущего пункта меню
        sf::Font font;                  // Шрифт меню
        // Динамический массив текстовых объектов названий пунктов меню
        sf::Text *mainMenu;
        sf::Color menuTextColor = sf::Color::White;    // Цвет пунктов меню
        sf::Color choseTextColor = sf::Color::Yellow;  // Цвет выбора пункта меню
        sf::Color borderColor = sf::Color::Black;       // Цвет обводки текста пунктов меню

        // Настройка текста пунктов меню
        // Параметры: ссылка на текстовый объект, текст, координаты текста
        void setInitText(sf::Text &text, sf::String str, float xpos, float ypos);

        // Ссылка на графическое окно
        sf::RenderWindow &mywindow;
    public:
        // Конструктор
        // Параметры: ссылка на графическое окно, координаты игрового меню по x и y
        // количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
        GameMenu(sf::RenderWindow &window, float menux, float menuy,
                 int index, sf::String name[], int sizeFont = 60, int step = 80);

        ~GameMenu() {
            delete[] mainMenu;
        }

        void draw();        // Рисуем меню

        void MoveUp();     // Перемещение выбора меню вверх

        void MoveDown();   // Перемещение выбора меню вниз

        // Цвет элементов игрового меню
        void setColorTextMenu(sf::Color menColor, sf::Color ChoColor,
                              sf::Color BordColor);

        void alignMenu(int posx);   // Выравнивание положения меню

        int getSelectedMenuNumber(){ // Возвращает номер выбранного элемента меню
            return mainMenuSelected;
        }
    };
}