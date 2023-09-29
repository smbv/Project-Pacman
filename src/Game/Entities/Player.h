#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "State.h"
#include "powerUp.h"

enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health = 3;
        int score = 0;
        bool StrawberryOn = false;
        int StrawberryCountdown = 0;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;

        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        PowerUp *powerUp;
        PowerUp *speedBoost; //pointers to the powerups
        PowerUp *randomPowerUp;
        PowerUp *strawberryPowerUp;
        PowerUp *cherryPowerUp;


    public:
        Player(int, int, int , int, EntityManager*,ofImage);// we add ofImage here to be able to use the mapsize so we can correctly do cherrypowerup
        ~Player();
        ofImage mapcreator; //this is to get the map size
        //getters
        int getHealth();
        int getScore();
        int getSpeed();
        FACING getFacing();

        //setters 
        void setSpeed(int);
        void setXposition(int);// this is for changing the position of the pacman
        void setYposition(int);
        void setHealth(int);
        void setScore(int);
        void setInvincible(bool);// to set when strawberry is active
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        bool invincible = false;
};