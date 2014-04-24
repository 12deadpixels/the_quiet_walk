/***************
manager
 //cc. non commercial share alike Tom Schofield, Source Code licenced under GNU v3 2011
*****************/

#ifndef __manager__
#define __manager__

#include "ofMain.h"
#include "scene.h"
#include "welcomeScene.h"
#include "readyScreen.h"
#include "directionScene.h"
#include "endScene.h"
#include "listenScene.h"
#include "mapScene.h"
#include "ofxiWebUploader.h"

#define MAX_POSS_ATTEMPTS 6

using namespace std;


class manager{
    public:
    void setup();
    void update(float _lat, float _long);
    void touch(ofPoint touch);
    void nextScene();
    void previousScene();
    void goToScene(int _sceneIndex);

    void start();
    void stop();
    void draw();
    bool playBack;
    
    bool getIsRecording();
    bool getIsListening();
    bool getSampleIsReady();
    bool getPageOpened();
    
    void setWasQuiet(bool _wasQuiet);
    void setPageOpened(bool _pageOpened);
    void setSampleIsReady(bool _sampleIsReady);
    
    void addAudioLevel(float level);
protected:
    bool frameHasEnded();
    bool frameHasStarted();
    vector<scene *> scenes;

    welcomeScene wel;
    readyScreen red;
    directionScene dir;
    listenScene lis;
    endScene end;
    mapScene mmap;
    int sceneIndex;
    bool isRecording;
    int numAttempts;
    bool wasQuiet;
    bool isListening;
    bool pageOpened;
    bool sampleIsReady;
    vector <float> audioLevels;
    vector <float> audioLevelsOneLocation;
    vector<float> lats;
    vector<float> longs;
    ofxiWebUploader uploader;
    ofSoundPlayer startTone;
    ofSoundPlayer quietTone;
    ofSoundPlayer loudTone;

    string headerphp;
	string uploadphp;
	string footerphp;
    
};

#endif

