#pragma once

#include"Card.h"


class Redactor{
private:
    Card card;
    int y = 0;
public:
    Redactor() = default;
    ~Redactor() = default;

    void setItem(int x, int y, char value);
    void save();
    int get_y();
    Card get_Card();
    void setCard(Card& card);
};