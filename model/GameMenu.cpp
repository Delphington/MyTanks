#include "GameMenu.h"

// метод настройки текстовых объектов пунктов игрового меню
void game::GameMenu::setInitText(sf::Text& text, sf::String str, float xpos, float ypos){
    text.setFont(font);                 // шрифт
    text.setFillColor(menuTextColor); // цвет
    text.setString(str);                // текст
    text.setCharacterSize(sizeFont);   // размер шрифта
    text.setPosition(xpos, ypos);       // координаты текстового объекта
    text.setOutlineThickness(3);        // толщина контура обводки текста
    text.setOutlineColor(borderColor); // цвет контура обводки текста
}
// Выравнивание пунктов меню по левому по правому по центру 
void game::GameMenu::alignMenu(int posx){
    float nullx = 0;
    for (int i = 0; i < maxMenu; i++) {
        switch (posx){
            case 0:
                nullx = 0; // выравнивание по правому краю от установленных координат
                break;
            case 1:
                nullx = mainMenu[i].getLocalBounds().width;  // по левому краю
                break;
            case 2:
                nullx = nullx = mainMenu[i].getLocalBounds().width / 2;  // по центру
                break;
        }
        mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
    }
}
// Конструктор
game::GameMenu::GameMenu(sf::RenderWindow& window, float menux, float menuy,
                         int index, sf::String name[], int sizeFont, int step)
        :mywindow(window), menuX(menux), menuY(menuy), sizeFont(sizeFont), menuStep(step){
    // Загрузка шрифта
    if (!font.loadFromFile("resourse/setting/Arial.ttf")) exit(32);
    maxMenu = index; // Количество єлементов меню
    mainMenu = new sf::Text[maxMenu];     // Динамический массив пунктов меню
    // Выстраиваем элементы меню
    for (int i = 0, ypos = menuY; i < maxMenu; i++, ypos += menuStep) setInitText(mainMenu[i], name[i], menuX, ypos);
    mainMenuSelected = 0; // Задаём начальное положения выбраного пункта меню
    // цвет выбраного пункта меню
    mainMenu[mainMenuSelected].setFillColor(choseTextColor);
}
// перемещение выбора меню вверх
void game::GameMenu::MoveUp(){
    mainMenuSelected--;
    // подсвечиваем выбранный пункт меню
    if (mainMenuSelected >= 0) {
        mainMenu[mainMenuSelected].setFillColor(choseTextColor);
        mainMenu[mainMenuSelected + 1].setFillColor(menuTextColor);
    }
    else{
        mainMenu[0].setFillColor(menuTextColor);
        mainMenuSelected = maxMenu - 1;
        mainMenu[mainMenuSelected].setFillColor(choseTextColor);
    }
}
// перемещение выбора меню вниз
void game::GameMenu::MoveDown(){
    mainMenuSelected++;
// подсвечиваем выбранный пункт меню
    if (mainMenuSelected < maxMenu) {
        mainMenu[mainMenuSelected - 1].setFillColor(menuTextColor);
        mainMenu[mainMenuSelected].setFillColor(choseTextColor);
    }
    else{
        mainMenu[maxMenu - 1].setFillColor(menuTextColor);
        mainMenuSelected = 0;
        mainMenu[mainMenuSelected].setFillColor(choseTextColor);
    }

}
// рисуем элементы меню в графическом окне
void game::GameMenu::draw(){
    // перебираем для отрисовки существующие текстовые объекты пунктов меню
    for (int i = 0; i < maxMenu; i++) mywindow.draw(mainMenu[i]);
}
// назначение цвета элементам пунктов меню
void game::GameMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
    menuTextColor = menColor;   // цвет пунктов меню
    choseTextColor = ChoColor; // цвет выбраного пункта меню
    borderColor = BordColor;    // цвет контура пунктов меню

    for (int i = 0; i < maxMenu; i++) {
        mainMenu[i].setFillColor(menuTextColor);
        mainMenu[i].setOutlineColor(borderColor);
    }

    mainMenu[mainMenuSelected].setFillColor(choseTextColor);
}