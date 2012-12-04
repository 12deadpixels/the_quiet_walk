#include "endScene.h"
////////////////////////---------/////////////////////////////////////
void endScene::setup(){
    successEnd.loadImage("images/Screen04.png");
    failureEnd.loadImage("images/Screen06.png");
}
void endScene::start(){
    sceneHasEnded = false;
    pageOpened= false;
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
        h= 28;
    }else{
        buttPos = ofPoint(160,454);
        w = 92;
        h= 28;
    }
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
    else{
    pageOpened= true;
        cout<<"page opened in endSCene"<<endl;

    }

 // [[UIApplication sharedApplication] openURL:[NSURL URLWithString:ofxStringToNSString(url)]];
    
}
bool endScene::getPageOpened(){
    return pageOpened;
}
void endScene::setPageOpened(bool _pageOpened){
    pageOpened=_pageOpened;
}