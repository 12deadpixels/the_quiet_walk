/***************
mapScene
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __mapScene__
#define __mapScene__

#include "ofMain.h"
#include "scene.h"
#include "ofxHeatMap.h"

//#include "ofxiPhoneExtras.h"

using namespace std;


class mapScene : public scene{
    public:
    void setup();
    void start();
    void start(vector<float>_lats,vector<float>_longs, vector<float>_audioVals );
    void draw();
    void stop();
    void update();
    bool getSceneHasEnded();
    void touch(ofPoint touch);
protected:
    bool sceneHasEnded;
    bool sceneHasStarted;
    ofImage welcomeScreen;
    vector<float>lats;
    vector<float>longs;
    vector<float>audioVals;
    ofxHeatMap heatMap;

    ofImage heatImage;
    ofPoint mins;
    ofPoint maxs;


};

#endif

