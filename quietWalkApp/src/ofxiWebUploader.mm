#include "ofxiWebUploader.h"


ofxiWebUploader::ofxiWebUploader()
{
}

ofxiWebUploader::~ofxiWebUploader()
{
}

string ofxiWebUploader::send( string myUrl, vector<string> keys, vector<string>vals, int mode)
{
	if( mode == WEB_GET )
	{
		string queryUrl = myUrl + "?";
		for( int i = 0; i < keys.size(); i++)
		{
			if( vals.size() > i )
			{
				if( i != 0 ) queryUrl += "&";
				queryUrl += keys[i] + "=" + vals[i];
			}
			
		}
		
		NSString *sUrl = [[[NSString alloc] initWithUTF8String:queryUrl.c_str()] autorelease];
		
		NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@",sUrl]];
		NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:url];
		NSURLResponse		*res = nil;
		NSError				*err = nil;
		
		NSData *data = [NSURLConnection sendSynchronousRequest:req returningResponse:&res error:&err];
		
		NSString *s = [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
		string str = [s UTF8String];
		return str;
		
	}
	else if( mode == WEB_POST)
	{
		
		// set up url
        
		NSString *sUrl	= [[[NSString alloc] initWithUTF8String:myUrl.c_str() ] autorelease ];
		NSURL *url		= [NSURL URLWithString:[NSString stringWithFormat:@"%@",sUrl]];
		NSMutableURLRequest *postRequest = [NSMutableURLRequest requestWithURL:url];
		
		// adding header information:
		[postRequest setHTTPMethod:@"POST"];
		
		// boundary -- not sure about boundaries, but this works for me
		NSString *stringBoundary = [NSString stringWithString:@"0xKhTmLbOuNdArY"];
		NSString *contentType	 = [NSString stringWithFormat:@"multipart/form-data; boundary=%@",stringBoundary];
		[postRequest addValue:contentType forHTTPHeaderField: @"Content-Type"];
		
		
		//setting up the body:
		NSMutableData *postBody = [NSMutableData data];
		[postBody appendData:[[NSString stringWithFormat:@"--%@\r\n",stringBoundary] dataUsingEncoding:NSUTF8StringEncoding]];
		
		for( int i = 0; i < keys.size(); i++)
		{
			if( vals.size() > i )
			{
				NSString *mkey	= [[[NSString alloc] initWithUTF8String:keys[i].c_str()] autorelease ];
				NSString *mval	= [[[NSString alloc] initWithUTF8String:vals[i].c_str()] autorelease ];
				
				[postBody appendData:[[NSString stringWithFormat:@"Content-Disposition: form-data; name=\"%@\"\r\n\r\n",mkey] dataUsingEncoding:NSUTF8StringEncoding]];
				[postBody appendData:[[NSString stringWithFormat:@"%@",mval] dataUsingEncoding:NSUTF8StringEncoding]];
				
				[postBody appendData:[[NSString stringWithFormat:@"\r\n--%@\r\n",stringBoundary] dataUsingEncoding:NSUTF8StringEncoding]];
				
			}
			
		}
		
        
		[postRequest setHTTPBody:postBody];
		
		NSURLResponse	* response;
		NSError			* error;
		
		NSData* result = [NSURLConnection sendSynchronousRequest:postRequest returningResponse:&response error:&error];
		NSString * responseString = [[[NSString alloc] initWithData:result encoding:NSUTF8StringEncoding] autorelease];
		
		string str = [responseString UTF8String];
		return str;
        
	}else{
        
		cout << "Please set send mode to either: WEB_GET or WEB_POST" << endl;
	}
	
	return "No repsonse";
}
