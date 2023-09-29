#include "CherryPowerUp.h"



void CherryPowerUp::powerOn(){
    int xwindow = (ofGetWidth() - p->mapcreator.getWidth()*16)/2;//coorects windowsize, thx mapbuilder
    int ywindow = (ofGetHeight() - p->mapcreator.getHeight()*16)/2;
    std::vector<int>Coordinatex;//vectors to save the coordinates 
    std::vector<int>coordinatey;
    Coordinatex.push_back(9*16+xwindow);
    Coordinatex.push_back(25*16+xwindow);
    coordinatey.push_back(10*16+ywindow);
    coordinatey.push_back(22*16+ywindow);
    p->setXposition(Coordinatex[ofRandom(2)]);// randomizes the location of pacman using vectors
    p->setYposition(coordinatey[ofRandom(2)]);

    
}

void CherryPowerUp::deactivate(){

}