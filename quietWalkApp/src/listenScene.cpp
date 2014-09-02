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
    int targetTime = 60; // set the maximum time interval
    int cTime = targetTime - (ofGetElapsedTimeMillis()-millis)/1000;
    //ofDrawBitmapString(ofToString(cTime), ofGetWidth()/2 - 10, ofGetHeight()/2 + 30, 120);
    ofPopStyle();
    
    
    testFont.loadFont("fonts/Courier New Bold.ttf",32);
    testFont.drawString(ofToString(cTime),(ofGetWidth()/2)-20,632);
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