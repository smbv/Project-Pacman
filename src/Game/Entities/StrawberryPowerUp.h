#pragma once

#include "PowerUp.h"
#include "Player.h"

class StrawberryPowerUp : public PowerUp{

private:
Player *p;

    public:
    StrawberryPowerUp(Player *p){
     this->p = p;}

    void powerOn();
    void deactivate();
};