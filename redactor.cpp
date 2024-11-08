#include"redactor.h"

int Redactor::get_y(){
    return y;
}

void Redactor::setItem(int x, int y,char val){
    y = 1;
    card.setItemCard(y/50,x/50,val);
}

Card Redactor::get_Card(){
    return card;
}

void Redactor::setCard(Card& card_){
    y = 1;
    card = card_;
}