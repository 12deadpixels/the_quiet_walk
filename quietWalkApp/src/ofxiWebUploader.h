#ifndef WEBUPLOADER_H
#define WEBUPLOADER_H

#include "ofMain.h"

#define WEB_POST		0
#define WEB_GET			1

class ofxiWebUploader
{
public:
    ofxiWebUploader();
    virtual ~ofxiWebUploader();
    
    string	send( string myUrl, vector<string> keys, vector<string>vals, int mode );
    
    
protected:
    
	
private:
};

#endif // WEBUPLOADER_H
