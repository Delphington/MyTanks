#pragma once
#include <string>

class Config {
    Config() {}; // Конструктор по умолчанию
public:
    static const std::string nameGame;

    // Размеры экрана
    static const float SCREEN_WIDTH;
    static const float SCREEN_HEIGHT;


    // Размер пули
    const static float BULLET_HEIGHT;
    const static float BULLET_WIDTH;

    //-------------------------------
    static const int DEFAULT_SCORE;
    static const int P1_DEFAULT_LOCATE_X;
    static const int P1_DEFAULT_LOCATE_Y;
    static const int P2_DEFAULT_LOCATE_X;
    static const int P2_DEFAULT_LOCATE_Y;
    //-------------------------------

    static const int MENU_X;
    static const int MENU_Y;
    static const int MENU_INDEX;
    static const int MENU_SIZE_FONT;
    static const int MENU_FONT_STEP;

    // Меню
    static const std::string MENU_GAME;
    static const std::string MENU_SETTING;
    static const std::string MENU_ABOUT;
    static const std::string MENU_EXIT;

    static const std::string MENU_SETTING_BUTTON;


    //------------------------
    static const unsigned MENU_GAME_SIZE_SCORE;

    static const int MENU_GAME_SCORE1_POSITION_X;
    static const int MENU_GAME_SCORE1_POSITION_Y;
    static const int MENU_GAME_SCORE2_POSITION_X;
    static const int MENU_GAME_SCORE2_POSITION_Y;
};

