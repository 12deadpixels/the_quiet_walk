/***************
readyScreen
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __readyScreen__
#define __readyScreen__

#include "ofMain.h"
#include "scene.h"

using namespace std;


class readyScreen : public scene{
    public:
    void setup();
    void start();
    void draw();
    void stop();
    void update();
    bool getSceneHasEnded();
    void touch(ofPoint touch);
protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    ofImage readyScreenImage;
    float drawCounter;
    float x2 ;
    float y2 ;
    float radius;
};

#endif

