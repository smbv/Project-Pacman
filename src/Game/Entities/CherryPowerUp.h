#pragma once

#include "MapBuilder.h"
#include "PowerUp.h"
#include "Player.h"





class CherryPowerUp : public PowerUp{

private:
Player *p;

    public:


    CherryPowerUp(Player *p){
     this->p = p;}

    void powerOn();
    void deactivate();
};