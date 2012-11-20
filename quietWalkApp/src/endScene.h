/***************
endScene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __endScene__
#define __endScene__

#include "ofMain.h"
#include "scene.h"

using namespace std;


class endScene : public scene{
    public:
    void setup();
    void start();
    void draw();
    void stop();
    void update();
    bool getSceneHasEnded();
    void setState(int _state);
    void touch(ofPoint touch);

protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    ofImage successEnd, failureEnd;
    int state;
};

#endif

