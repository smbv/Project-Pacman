#include "StrawberryPowerUp.h"

void StrawberryPowerUp::powerOn(){

    p->setInvincible(true);
}

void StrawberryPowerUp::deactivate(){

     p->setInvincible(false);
}