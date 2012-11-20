/***************
welcomeScene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __welcomeScene__
#define __welcomeScene__

#include "ofMain.h"
#include "scene.h"

using namespace std;


class welcomeScene : public scene{
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
    ofImage welcomeScreen;
   
};

#endif

