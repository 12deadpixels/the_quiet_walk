/***************
listenScene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __listenScene__
#define __listenScene__

#include "ofMain.h"
#include "scene.h"

using namespace std;


class listenScene : public scene{
    public:
    void setup();
    void start();
    void draw();
    void stop();
    void update();
    bool getEndState();
    bool getSceneHasEnded();
    
protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    ofImage listenImage;
    bool wasQuiet;
    long millis;
    
};

#endif

