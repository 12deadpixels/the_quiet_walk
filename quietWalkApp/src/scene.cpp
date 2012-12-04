#include "scene.h"
////////////////////////---------/////////////////////////////////////
void scene::setup(){
    
}
void scene::start(){
    playBack=false;
    
}
void scene::start(vector<float>lats,vector<float>longs, vector<float>audioVals ){
    
}
bool scene::getSceneHasEnded(){
    return sceneHasEnded;
}
void scene::update(){
    
}
void scene::draw(){
}

void scene::stop(){
    
}
bool scene::getIsRecording(){
    return false;
}
bool scene::getPageOpened(){
}
void scene::touch(ofPoint touch){
    
}
bool scene::inBounds(ofPoint topLeft, float w, float h, ofPoint point){
    if(point.x>topLeft.x && point.x<topLeft.x+w && point.y > topLeft.y && point.y < topLeft.y+h){
        return true;
    }else{
        return false;
    }
}
bool scene::getEndState(){
    
}
void scene::setState(int state){
    
}
void scene::setPageOpened(bool _pageOpened){
    
}