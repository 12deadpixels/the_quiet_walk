#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "manager.h"
class testApp : public ofxiPhoneApp{
	
public:
	void setup();
	void update();
	void draw();
	
    void exit();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
	
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);

	void audioIn(float * input, int bufferSize, int nChannels);

	int	initialBufferSize;
	int	sampleRate;
	int	drawCounter;
    int bufferCounter;
	float * buffer;
    vector<float> longBuffer;
    //GPS
    ofxiPhoneCoreLocation * coreLocation;
	float heading;
	bool hasCompass;
	bool hasGPS;
    
    manager sceneManager;
    float av;
    int quietCount;
    int loudCount;

    /*
     1 welcome screen
     2 directions/that was loud+directions
     3 either back to 2, or that sounds quiet or there's no quiet here
     then generate a number of random instructions -> listen -> that was load or quiet
     
     
     */
};

