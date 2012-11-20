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
    ofPoint buttPos = ofPoint(117,417);
    float w = 97;
    float h= 27;
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
}