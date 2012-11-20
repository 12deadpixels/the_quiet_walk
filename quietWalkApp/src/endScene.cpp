#include "endScene.h"
////////////////////////---------/////////////////////////////////////
void endScene::setup(){
    successEnd.loadImage("images/Screen04.png");
    failureEnd.loadImage("images/Screen06.png");
}
void endScene::start(){
    sceneHasEnded = false;
}
void endScene::draw(){
    ofPushStyle();
    if(state==0){
        successEnd.draw(0, 0);
    }
    else{
        failureEnd.draw(0, 0);
    }
    ofPopStyle();
}
void endScene::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
}
void endScene::update(){
    
}
bool endScene::getSceneHasEnded(){
    return sceneHasEnded;
}
void endScene::setState(int _state){
    state=_state;
}
void endScene::touch(ofPoint touch){
    ofPoint buttPos;
    float w ,h;
    if(state==0){
        buttPos = ofPoint(160,423);
        w = 82;
        h= 18;
    }else{
        buttPos = ofPoint(160,454);
        w = 92;
        h= 18;
    }
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
}