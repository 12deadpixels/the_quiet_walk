#include "welcomeScene.h"
////////////////////////---------/////////////////////////////////////
void welcomeScene::setup(){
    welcomeScreen.loadImage("images/Screen00.png");
}
void welcomeScene::start(){
    sceneHasEnded = false;

}
void welcomeScene::draw(){
    ofPushStyle();
    welcomeScreen.draw(0, 0);
    ofPopStyle();
}
void welcomeScene::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
}
void welcomeScene::update(){
    
}
bool welcomeScene::getSceneHasEnded(){
    return sceneHasEnded;
}
void welcomeScene::touch(ofPoint touch){
    ofPoint buttPos = ofPoint(241,860);
    float w = 224;
    float h= 220;
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
}