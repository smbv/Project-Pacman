#include "Cherry.h"

Cherry::Cherry(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet, 489,49,16,16);
}
