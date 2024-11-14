#include "CollisionUtils.h"

// Коллизия при движении влево по OX
bool CollisionUtils::collXL(int dx, int dy, int w, Card& card) {
    if(card.getItemCard(dy/50, (dx - w - 10)/50 + 2) != 'X'
    && card.getItemCard((dy + 100)/50, (dx - w - 10)/50 + 2) != 'X'
    && card.getItemCard((dy + 50)/50, (dx - w - 10)/50 + 2) != 'X'
       && (dx -w + 90)/50 != 0)
        return false;
    return true;
}

// Коллизия при движении вправо по OX
bool CollisionUtils::collXR(int dx, int dy, int w, Card& card) {
    if(card.getItemCard(dy/50, (dx + w + 10)/50) != 'X'
    && card.getItemCard((dy + 50)/50, (dx + w + 10)/50) != 'X'
    && card.getItemCard((dy + 100)/50, (dx + w + 10)/50) != 'X')
        return false;
    return true;
}

// Коллизия при движении вверх по OY
bool CollisionUtils::collYU(int dx, int dy, int w, Card& card) {
    if(card.getItemCard((dy - w)/50 + 2, (dx)/50) != 'X'
    && card.getItemCard((dy-w)/50 + 2, (dx + 100)/50) != 'X'
    && card.getItemCard((dy-w)/50 + 2, (dx + 50)/50) != 'X'
       && (dy - w + 90)/50 != 0)
        return false;
    return true;
}

// Коллизия при движении вниз по OY
bool CollisionUtils::collYD(int dx, int dy, int w, Card& card) {
    if(card.getItemCard((dy + w + 10)/50, dx/50) != 'X'
    && card.getItemCard((dy + w)/50, (dx + 50)/50) != 'X'
    && card.getItemCard((dy + w)/50, (dx + 100)/50) != 'X')
        return false;
    return true;
}
