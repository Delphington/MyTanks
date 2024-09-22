
class Card{
private:
    static const int HEIGHT = 18;
    static const int WIDTH = 32;
    char card[HEIGHT][WIDTH];

    void setInitialization() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                    //установка счета
                    if((i ==0 && j ==14) ||  (i ==0 && j ==17)){
                        card[i][j] = '0';
                    }else{
                        card[i][j] = 'X';
                    }
                } else {
                    card[i][j] = ' ';
                }
            }
        }
    }

public:
    Card() {
        setInitialization(); // Инициализация при создании объекта
    }

    static const int getHeight() { return HEIGHT; }
    static const int getWidth() { return WIDTH; }

    char getItemCard(int i, int j) {
        if ((i >= 0 && i < HEIGHT) && (j >= 0 && j < WIDTH)) {
            return card[i][j];
        }
        return '\0'; // Возвращаем нулевой символ в случае ошибки
    }

    void setItemCard(int i, int j, char value) {
        if ((i >= 0 && i < HEIGHT) && (j >= 0 && j < WIDTH)) {
            card[i][j] = value;
        }
    }
};
