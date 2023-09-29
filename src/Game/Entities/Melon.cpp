#include "Melon.h"

Melon::Melon(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 552,49,16,16);
}