/***************
directionScene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __directionScene__
#define __directionScene__

#include "ofMain.h"
#include "scene.h"
//how many times it will repeat if there is no quietness found
#define NUM_DIRECTIONS 11

using namespace std;


class directionScene : public scene{
    public:
    void setup();
    void start();
    void draw();
    void stop();
    void update();
    bool getSceneHasEnded();
    //bool getEndState();
    void touch(ofPoint touch);
    void setState(int state);
protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    bool isFirstRun;
    int directionSelector;
    vector<ofImage> directionImages;
    ofImage backgroundImage;
    ofImage repeatBackgroundImage;
    int endState;
   
};

#endif

