#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	// IMPORTANT!!! if your sound doesn't work in the simulator - read this post - which requires you set the input stream to 24bit!!
	//	http://www.cocos2d-iphone.org/forum/topic/4159
    
    //	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
    //    ofSetLogLevel(OF_LOG_SILENT);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
	ofBackground(255, 255, 255);
    
	//for some reason on the iphone simulator 256 doesn't work - it comes in as 512!
	//so we do 512 - otherwise we crash
	initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
	
	buffer = new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
    
	// 0 output channels,
	// 1 input channels
	// 44100 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
	ofSetFrameRate(60);
    
    
    //GPS Setup
	coreLocation = new ofxiPhoneCoreLocation();
	hasCompass = coreLocation->startHeading();
	hasGPS = coreLocation->startLocation();
	heading = 0.0;
    
    sceneManager.setup();
    sceneManager.start();
    
    //  example uploader stuff
    //    string response = uploader.send(uploadphp, keys,vals,WEB_POST);
    //    cout << "post responseUploader :  \n" << response << endl;
    
    av=0;
    quietCount=loudCount=0;
    // mapKit.open();
}

//--------------------------------------------------------------
void testApp::update(){
    //ofPoint  loc = mapKit.getScreenCoordinatesForLocation(coreLocation->getLatitude(),coreLocation->getLongitude());
    //cout<<loc<<" loc: "<<coreLocation->getLatitude();
    sceneManager.update(coreLocation->getLatitude(),coreLocation->getLongitude());
    //sceneManager.update(loc.x,loc.y);
    if(sceneManager.getPageOpened()){
        string url = "http://di.ncl.ac.uk/quietwalk/map.html";
        cout<<"page opened in testApp"<<endl;
        ofxiPhoneLaunchBrowser(url);
//        sceneManager.setPageOpened(false);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    //
    //	ofTranslate(0, -50, 0);
    //
    //	// draw the input:
    //	ofSetHexColor(0x333333);
    //	ofRect(70, 100, 256, 200);
    //	ofSetHexColor(0xFFFFFF);
    //	for(int i = 0; i < initialBufferSize; i++){
    //		ofLine(70 + i, 200, 70 + i, 200 + buffer[i] * 100.0f);
    //	}
    //
    //	ofSetHexColor(0x333333);
    //	drawCounter++;
    //	char reportString[255];
    //	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter, drawCounter);
    //	ofDrawBitmapString(reportString, 70, 308);
    sceneManager.draw();
    ofCircle(100, 100, av*100);
}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    /*
     35db = 0.0004
     
     45db = 0.002
     
     55db = 0.0038
     
     70db = 0.025
     
     87db = 0.16
     */
	if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}
	
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
	}
	bufferCounter++;
    
    //take a rough average.
    float average=0.0;
    
    //just take the last part of the buffer
    for(int i = 0; i < 16; i++){
		average+=ABS(buffer[i]);
	}
    average/=16.0;
    
    if(sceneManager.getIsListening()){
        float thresh=0.05;
        int numHighSamples=10;
        //        float thresh=4.7;
        
        // cout<<"average "<<average<<" ";
        if (average>thresh) {
            loudCount++;
        }
        cout<<endl<<loudCount<<" "<<quietCount<<" "<<average<<endl;
        if (loudCount>numHighSamples) {
            sceneManager.setWasQuiet(false);
        }
        else{
            sceneManager.setWasQuiet(true);
        }
        sceneManager.addAudioLevel(average);
    }
    else{
        longBuffer.clear();
        av=0;
        quietCount=loudCount=0;
        
    }
    
    
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    ofPoint aTouch = ofPoint(touch.x,touch.y);
    sceneManager.touch(aTouch);
   
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    
}
void testApp::ofxiPhoneLaunchBrowser(string url) {

  [[UIApplication sharedApplication] openURL:[NSURL URLWithString:ofxStringToNSString(url)]];

}
