#include "RandomPowerUp.h"
#include "Melon.h"

void RandomPowerUp::powerOn(){

    p->setScore(p->getScore() + rand() % 4000 + 400);

}

void RandomPowerUp::deactivate(){
    
}