#pragma once
#include "powerUp.h"
#include "Player.h" 

class SpeedBoost : public PowerUp{
    private:
    Player * p; 

    public:
    SpeedBoost(Player * p ){
        this -> p = p;
    }
    void powerOn();
    void deactivate();
};