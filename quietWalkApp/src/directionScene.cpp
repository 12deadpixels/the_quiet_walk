#include "directionScene.h"
////////////////////////---------/////////////////////////////////////
void directionScene::setup(){
    for(int i=0;i<NUM_DIRECTIONS;i++){
        string fName = "images/t"+ofToString(i)+".png";
        ofImage temp;
        temp.loadImage(fName);
        directionImages.push_back(temp);
    }
    repeatBackgroundImage.loadImage("images/Screen03.png");
    backgroundImage.loadImage("images/Screen03a.png");
    isFirstRun=true;
}
void directionScene::start(){
    directionSelector = (int) ofRandom(0, directionImages.size()-1);
    endState=0;
    sceneHasEnded = false;

}
void directionScene::draw(){
    ofBackground(0, 0, 0);
    ofPushStyle();
    ofPoint dirPos = ofPoint(170,326);
    if (isFirstRun) {
        backgroundImage.draw(0, 0);
    }
    else{
        repeatBackgroundImage.draw(0, 0);
    }
    directionImages[directionSelector].draw(dirPos);
    ofPopStyle();
}
void directionScene::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
    isFirstRun=false;
}
void directionScene::update(){
    
}
bool directionScene::getSceneHasEnded(){
    return sceneHasEnded;
}
void directionScene::touch(ofPoint touch){
    ofPoint buttPos = ofPoint(210,745);
    float w = 325;
    float h= 300;
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
}
void directionScene::setState(int state){
    if(state==0){
        isFirstRun=true;
    }
    else{
        isFirstRun=false;
    }
}