#include "readyScreen.h"
////////////////////////---------/////////////////////////////////////
void readyScreen::setup(){
    readyScreenImage.loadImage("images/Screen01a.png");
}
void readyScreen::start(){
    sceneHasEnded = false;
    drawCounter =0.0f;
     x2 = ofGetWidth()/2;
     y2 = ofGetHeight()/1.5;
}
void readyScreen::draw(){
    ofPushStyle();
    ofColor(255);
    readyScreenImage.draw(0, 0);
    
    ofNoFill();
    radius = 50 + 2 * sin(drawCounter);
    ofCircle(x2,y2,radius);    
    ofCircle(x2,y2,radius - 30);
    ofCircle(x2,y2,radius - 10);

    ofPopStyle();
}
void readyScreen::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
}
void readyScreen::update(){
    drawCounter= drawCounter + 0.033f;
}
bool readyScreen::getSceneHasEnded(){
    return sceneHasEnded;
}
void readyScreen::touch(ofPoint touch){
    ofPoint buttPos = ofPoint(70,115);
    float w = 171;
    float h= 58;
    cout<<"touched";
    float halfRad = 0.5f*radius;
    ofPoint circPos=ofPoint(x2-halfRad, y2-halfRad  );
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
   
    else if(inBounds(circPos,radius,radius,touch)){
         stop();
    }
}