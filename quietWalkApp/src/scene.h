/***************
scene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __scene__
#define __scene__

#include "ofMain.h"

using namespace std;


class scene{
public:
    virtual void setup();
    virtual void start();
    virtual void start(vector<float>lats,vector<float>longs, vector<float>audioVals );

    virtual void draw();
    virtual void stop();
    virtual bool getSceneHasEnded();
    virtual void update();
    virtual bool getIsRecording();
    virtual void touch(ofPoint touch);
    virtual bool getEndState();
    virtual void setState(int state);
    bool playBack;
protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    string fileName;
    ofTrueTypeFont font;
    virtual bool inBounds(ofPoint topLeft, float w, float h, ofPoint point);
   
};

#endif

