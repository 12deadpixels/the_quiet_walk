#include "mapScene.h"
////////////////////////---------/////////////////////////////////////
void mapScene::setup(){
    
}
void mapScene::start(vector<float>_lats,vector<float>_longs, vector<float>_audioVals ){
    lats=_lats;
    longs=_longs;
    audioVals=_audioVals;
 //   mapKit.open();
    ofPoint audioMinMax=ofPoint(0,0);

    
  /* for (int i=0; i<lats.size(); i++) {
        lats[i]=ofRandom(-180.0,180.0);
        longs[i]=ofRandom(-180.0,180.0);
    }
    for (int i=0; i<lats.size(); i++) {
        if(lats[i]!=0 || longs[i]!=0){
            cout<<lats[i]<<" LATS "<<i<<" "<<maxs.x<<endl;
            maxs.x= MAX(maxs.x, lats[i]);
            maxs.y= MAX(maxs.y, longs[i]);
            mins.x= MIN(mins.x, lats[i]);
            mins.y= MIN(mins.y, longs[i]);
            audioMinMax.x=MAX(audioMinMax.x, audioVals[i]);
            audioMinMax.y=MIN(audioMinMax.y, audioVals[i]);

        }
    }
    
    for (int i=0; i<lats.size(); i++) {
        lats[i]=ofMap(lats[i],mins.x, maxs.x ,0,ofGetWidth());
        longs[i]=ofMap(longs[i],mins.y, maxs.y ,0,ofGetHeight());
        audioVals[i]=ofMap(audioVals[i], audioMinMax.x, audioMinMax.y, 0.0, 1.0);
        cout<<"AUDIO VALS "<<i<<" "<<audioVals[i]<<endl;
    }
    cout<<"MAKING HEATMAP:"<<endl;
    heatImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    int numPix=ofGetWidth()* ofGetHeight();
    //unsigned char *pixels = new unsigned char[numPix];
    int x=0;
    int y=0;
    ofPixels  pixels;
    pixels.allocate(ofGetWidth(), ofGetHeight(), 3);
    for(int i=0;i<numPix;i++){
        ofColor aColour;
        float hue = heatMap.getInterpValue(x, y, lats,longs,audioVals);
        aColour.setHsb(hue*255, 255, 255);
        pixels.setColor(x, y,aColour);        //= heatMap.getInterpValue(x, y, lats,longs,audioVals);
        x++;
        if(x>=heatImage.getWidth()){
            x=0;
            y++;
        }
        
    }
    
   heatImage.setFromPixels (pixels);*/
    cout<<"MADE HEATMAP:"<<endl;

}
void mapScene::start(){
    sceneHasEnded = false;
}
void mapScene::draw(){
    ofPushStyle();
    ofBackground(0, 0, 0);
    //ofSetColor(252, 0, 0);
    

   // heatImage.draw(0,0);
   // cout<<" lats.size() "<< lats.size() <<endl;
    
    //cout<<"MIN AND MAX: "<<mins.x<<" "<<maxs.x<<" "<<mins.y<<" "<< maxs.y<<endl;
    for (int i=0; i<lats.size(); i++) {
//        ofCircle(ofMap(lats[i],mins.x, maxs.x ,0,ofGetWidth()) , ofMap(longs[i],mins.y, maxs.y ,0,ofGetHeight()), 10.0*audioVals[i]);
        ofDrawBitmapString(ofToString(audioVals[i]), lats[i] , longs[i]);

    }
    ofPopStyle();
}
void mapScene::stop(){
    sceneHasEnded = true;
    cout<<"sceneHasEnded ";
}
void mapScene::update(){
    
}
bool mapScene::getSceneHasEnded(){
    return sceneHasEnded;
}
void mapScene::touch(ofPoint touch){
    ofPoint buttPos = ofPoint(117,417);
    float w = 97;
    float h= 27;
    cout<<"touched";
    if(inBounds(buttPos,w,h,touch)){
        stop();
    }
}