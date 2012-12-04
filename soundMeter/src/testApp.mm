#include "testApp.h"
float peaks;
float decay = 0.8;
float maxPeaks = 0.0;
float level = 0.0;
float thresh=0.05;
int loudCount=0;
bool isLoud=false;
bool wasLoud=false;

int numHighSamples=10;
bool isListening=false;
float lastAverage=0.0;
long aTime=0.0;
int sampleTime=2;
bool pIsListening;
//--------------------------------------------------------------
void testApp::setup(){

	// IMPORTANT!!! if your sound doesn't work in the simulator - read this post - which requires you set the input stream to 24bit!!
	//	http://www.cocos2d-iphone.org/forum/topic/4159

	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);

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
}

//--------------------------------------------------------------
void testApp::update(){
    if(isListening) {
        if (ofGetElapsedTimeMillis()-aTime>sampleTime*1000) {
            isListening=false;
        }
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){

	/*ofTranslate(0, -50, 0);

	// draw the input:
	ofSetHexColor(0x333333);
	ofRect(70, 100, 256, 200);
	ofSetHexColor(0xFFFFFF);
	for(int i = 0; i < initialBufferSize; i++){
		ofLine(70 + i, 200, 70 + i, 200 + buffer[i] * 100.0f);
	}

	ofSetHexColor(0x333333);
	drawCounter++;
	char reportString[255];
	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter, drawCounter);
	ofDrawBitmapString(reportString, 70, 308);
    
    peaks = MAX(peaks, maxPeaks);
    ofRect(peaks * (ofGetWidth()-50),0,50, 100);
    
    // smooth the decay, so the visual is less flicky
    peaks *= decay;
    //string levelString =
    if(ofGetFrameNum()%10==0){
        level=peaks;
    }
    ofDrawBitmapString(ofToString(level), 1, ofGetHeight()+40);*/
    ofBackground(0);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("isListenng : "+ofToString(isListening), 0,20);
    ofDrawBitmapString("thresh : "+ofToString(thresh), 0,50);
    ofDrawBitmapString("numHighSamplesPerSecond : "+ofToString(numHighSamples), 0,80);
    ofDrawBitmapString("lastAverage : "+ofToString(lastAverage), 0,110);
    ofDrawBitmapString("Last sample was Lound : "+ofToString(wasLoud), 0,140);

    ofRect(0, ofGetHeight()-ofMap(lastAverage,0,1,0,ofGetHeight()), ofGetWidth(), 10);
    
}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
			
	if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}	

	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
	}
    
	bufferCounter++;
    maxPeaks = 0.0;
    float average=0.0;

    // here I scan the latest n. bytes of the buffer
    for (int a=0; a<16; a++){
        maxPeaks = MAX(maxPeaks, ABS(buffer[a]));
        average+=ABS(buffer[a]);

    }
    average/=16.0;
    lastAverage=average;
    if (isListening) {
        if (average>thresh) {
            loudCount++;
        }
        //for a longer time we need more samples
        if (loudCount>numHighSamples*sampleTime){
            
            isLoud=true;
        }else{
            
            isLoud=false;
        }
    }
    else{
        if (pIsListening!=isListening) {
            wasLoud=isLoud;
        }
        loudCount=0;
    }
    pIsListening=isListening;
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    if (touch.x<100 && touch.y<30) {
        isListening=true;
        aTime = ofGetElapsedTimeMillis();
    }
    else{
        
    }
    cout<<touch.x<<" "<<touch.y<<endl;

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    if (touch.x<100 && touch.y<30) {
    }
    else{
        thresh = ofMap(touch.x, 0, ofGetWidth(), 0, 1.0);
        numHighSamples= ofMap(touch.y, 0, ofGetHeight(), 1, 25);
    }
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

