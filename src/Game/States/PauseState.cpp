#include "PauseState.h"

PauseState::PauseState() {
	resumeButton = new Button(ofGetWidth()/2, ofGetHeight()/2, 64, 50, "resume");
	quitButton = new Button(ofGetWidth()/2, (ofGetHeight()/2) + 30, 64, 50, "quit");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void PauseState::tick() {
	resumeButton->tick();
	quitButton->tick();
	anim->tick();
	if(resumeButton->wasPressed()){
		setNextState("Game");
		setFinished(true);

	}else if(quitButton->wasPressed()){
		setNextState("Menu");
		setFinished(true);
	}
}
void PauseState::render() {
	ofDrawBitmapString("Score: " + to_string(score), ofGetWidth()/2, ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2, ofGetHeight()/2-100, 100, 100);
	resumeButton->render();
	quitButton->render();


}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	resumeButton->mousePressed(x, y);
	quitButton->mousePressed(x, y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	resumeButton->reset();
	quitButton->reset();
}

void PauseState::setScore(int sc){
    score = sc;
}

PauseState::~PauseState(){
	delete resumeButton;
	delete quitButton;
	delete anim;
}