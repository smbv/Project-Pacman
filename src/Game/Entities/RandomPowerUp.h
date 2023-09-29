#pragma once

#include "PowerUp.h"
#include "Player.h"
#include "MapBuilder.h"


class RandomPowerUp : public PowerUp{

private:
Player *p;

    public:

    RandomPowerUp(Player *p){
     this->p = p;}

    void powerOn();
    void deactivate();
};