#include "listenScene.h"
////////////////////////---------/////////////////////////////////////
void listenScene::setup(){
    listenImage.loadImage("images/Screen02.png");
}
void listenScene::start(){
    wasQuiet=false;
    millis = ofGetElapsedTimeMillis();
    sceneHasEnded = false;

}
void listenScene::draw(){
    ofPushStyle();
    listenImage.draw(0, 0);
    int cTime = (ofGetElapsedTimeMillis()-millis)/1000;
    ofDrawBitmapString(ofToString(cTime), ofGetWidth()/2, ofGetHeight()/2);
    ofPopStyle();
}
void listenScene::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
}
void listenScene::update(){
    int secondsToListen = 60;
    if (ofGetElapsedTimeMillis()-millis>1000*(secondsToListen+1)) {
        //checkstatus;
       
        
        sceneHasEnded=true;
        
    }
    
}
bool listenScene::getSceneHasEnded(){
    return sceneHasEnded;
}
bool listenScene::getEndState(){
    return wasQuiet;
}