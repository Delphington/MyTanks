#include <string>

using namespace std;

class Config {
public:
    const string nameGame = "MyTanks";


    Config() {};

    const float SCREEN_WIGHT = 1600;
    const float SCREEN_HEIGHT = 900;

    //-------------------------------
    const int DEFAULT_SCORE = 0;
    const int P1_DEFAULT_LOCATE_X = 100;
    const int P1_DEFAULT_LOCATE_Y = 400;
    const int P2_DEFAULT_LOCATE_X = 1400;
    const int P2_DEFAULT_LOCATE_Y = 400;
    //-------------------------------

    //Menu
    const string MENU_START = "Start";
    const string MENU_SETTING = "Setting";
    const string MENU_ABOUT = "About game";
    const string MENU_EXIT = "Exit";

    const int MENU_X = 750;
    const int MENU_Y = 250;
    const int MENU_INDEX = 4;
    const int MENU_SIZE_FONT = 100;
    const int MENU_FONT_STEP = 120;



    // const int MENU_HOME_

};
// Инициализация статической переменной
