/***************
manager
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __manager__
#define __manager__

#include "ofMain.h"
#include "scene.h"
#include "welcomeScene.h"
#include "directionScene.h"
#include "endScene.h"
#include "listenScene.h"
#define MAX_POSS_ATTEMPTS 3

using namespace std;


class manager{
    public:
    void setup();
    void update();
    void touch(ofPoint touch);
    void nextScene();
    void previousScene();
    void goToScene(int _sceneIndex);
    void start();
    void stop();
    void draw();
    bool getIsRecording();
    bool playBack;
protected:
    bool frameHasEnded();
    bool frameHasStarted();
    vector<scene *> scenes;

    welcomeScene wel;
    directionScene dir;
    listenScene lis;
    endScene end;
    
    int sceneIndex;
    bool isRecording;
    int numAttempts;
    
};

#endif

