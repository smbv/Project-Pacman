#pragma once

#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Strawberry.h"
#include "Cherry.h"
#include "Melon.h"

class MapBuilder {
    public:
        MapBuilder();
	    Map* createMap(ofImage);

	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        ofColor boundBoundBlock;
        ofColor pacman;
        ofColor ghostC;
	    ofColor dotC;
	    ofColor bigDotC;
        ofColor StrawberryC;
        ofColor CherryC;
        ofColor MelonC;
        ofImage pacmanSpriteSheet;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
};