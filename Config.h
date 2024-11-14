#pragma once
#include <string>

class Config {
    Config() {}; // Конструктор по умолчанию
public:
    static const std::string nameGame;

    // Размеры экрана
    static const float SCREEN_WIDTH;
    static const float SCREEN_HEIGHT;

    //-------------------------------
    static const int DEFAULT_SCORE;
    static const int P1_DEFAULT_LOCATE_X;
    static const int P1_DEFAULT_LOCATE_Y;
    static const int P2_DEFAULT_LOCATE_X;
    static const int P2_DEFAULT_LOCATE_Y;
    //-------------------------------

    // Меню
    static const std::string MENU_START;
    static const std::string MENU_SETTING;
    static const std::string MENU_ABOUT;
    static const std::string MENU_EXIT;

    static const int MENU_X;
    static const int MENU_Y;
    static const int MENU_INDEX;
    static const int MENU_SIZE_FONT;
    static const int MENU_FONT_STEP;


    static const std::string MENU_SETTING_BUTTON;
};

