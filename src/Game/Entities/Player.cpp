#include "Player.h"
#include "CherryPowerUp.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "SpeedBoost.h"
#include "Strawberry.h"
#include "Cherry.h"
#include "Melon.h"
#include "RandomPowerUp.h"
#include "StrawberryPowerUp.h"

Player::Player(int x, int y, int width, int height, EntityManager* em,ofImage mp) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    this->mapcreator= mp;
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    moving = MLEFT;
    
}
void Player::tick(){

    speedBoost = new SpeedBoost(this);
    powerUp = nullptr;
    randomPowerUp = new RandomPowerUp(this);
    strawberryPowerUp = new StrawberryPowerUp(this);
    cherryPowerUp = new CherryPowerUp(this);

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
    }
    if (StrawberryOn == true){//timer
        if(StrawberryCountdown == 110){
            StrawberryCountdown = 0;//resets timer
            powerUp = strawberryPowerUp;
            StrawberryOn = false;
            powerUp->deactivate();
        }
        else{
            StrawberryCountdown += 1;
        }
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());

    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':  //changed infinite lives to max 3 lifes 
        if (this->getHealth() < 3){
            health++;
        }
        break;

        case ' ':// speed
        powerUp = speedBoost;
        powerUp->powerOn();
        break;
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

//getters
int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
int Player::getSpeed(){return speed;} 
FACING Player::getFacing(){ return facing; }

//setters 
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }
void Player::setSpeed(int sp){ this-> speed = sp;} 
void Player::setXposition(int xu){ x = xu;} 
void Player::setYposition(int yu){ y = yu;} 
void Player::setInvincible(bool n){invincible = n;}


void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=20;
                em->setKillable(true);
            }
            if(dynamic_cast<Strawberry*>(entity)){// make the sprite eatable and activate the powerups
                powerUp = strawberryPowerUp;
                strawberryPowerUp->powerOn();
                StrawberryOn = true; //activates timer so that way it stops briefly
                entity->remove = true;
            }
            if(dynamic_cast<Cherry*>(entity)){
                powerUp = cherryPowerUp;
                cherryPowerUp->powerOn();
                entity->remove = true;
            }
            if(dynamic_cast<Melon*>(entity)){
                powerUp = randomPowerUp;
                randomPowerUp->powerOn();
                entity->remove = true;
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if(ghost->getKillable()){
                ghost->remove = true;
            }
            else if(invincible == true){
                //this is so the ghost wont hurt
            }
            else{
                die();
            }
        }
    }

    
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}