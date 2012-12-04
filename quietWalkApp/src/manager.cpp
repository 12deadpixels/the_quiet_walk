#include "manager.h"
////////////////////////---------/////////////////////////////////////
void manager::setup(){
    
    scenes.push_back(&wel);
    scenes.push_back(&dir);
    scenes.push_back(&lis);
    scenes.push_back(&end);
   // scenes.push_back(&mmap);
    
    isRecording=false;
    playBack = false;
    pageOpened=false;
    for(int i=0;i<scenes.size();i++){
        scenes[i]->setup();
    }
    headerphp = "http://di.ncl.ac.uk/schofield_altavilla_quietwalk/header-decibels.php";
	uploadphp = "http://di.ncl.ac.uk/schofield_altavilla_quietwalk/uploadAll.php";
//	uploadphp = "http://di.ncl.ac.uk/schofield_altavilla_quietwalk/upload-decibels.php";
    
	footerphp = "http://di.ncl.ac.uk/schofield_altavilla_quietwalk/footer-decibels.php";
}
void manager::start(){
    
    cout<<"MANAGER START ";
    sceneIndex=0;
    //tell the direction scene that this is the first run
    scenes[1]->setState(0);
    scenes[sceneIndex]->start();
    numAttempts = 0;
    sampleIsReady=false;
    audioLevels.clear();
    audioLevelsOneLocation.clear();
    lats.clear();
    longs.clear();
    
}
void manager::update(float _lat, float _long){
    scenes[sceneIndex]->update();
    
    if(scenes[sceneIndex]->getPageOpened()){
        pageOpened=true;
        cout<<"page opened in manager"<<endl;

    }
    
    if (sceneIndex==2) {
        isListening=true;
    }
    else{
        isListening=false;
    }
    if(scenes[sceneIndex]->getSceneHasEnded()){
        cout<<"go to next scene";
        
        //first check if we need to swithc back because we are on the listening scene
        if (sceneIndex==2) {
            
          //  wasQuiet = scenes[sceneIndex]->getEndState();
            cout<<"WASQUIET "<<wasQuiet<<endl;
            //GO TO END AND FLAG FOR SUCCESS
            if(wasQuiet){
                cout<<"go to 3 QUIET"<<endl;
                goToScene(3);
                scenes[3]->setState(0);
            }
            //GO TO END AND FLAG FOR FAIL
            else if(numAttempts>=MAX_POSS_ATTEMPTS){
                cout<<"go to 3 NOT QUIET"<<endl;

                goToScene(3);
                scenes[3]->setState(1);

            }
            //GO TO DIRECTIONS AGAIN
            else if(numAttempts<MAX_POSS_ATTEMPTS){
                cout<<"go to 1"<<endl;

                numAttempts++;
                goToScene(1);
            }
            sampleIsReady=true;
            
            float average=0.0;
            for(int i=0;i<audioLevelsOneLocation.size();i++){
                average+=audioLevelsOneLocation[i];
            }
            average/=audioLevelsOneLocation.size();
            audioLevels.push_back(average);
            lats.push_back(_lat);
            longs.push_back(_long);
            cout<<average<<" bump up lat and long "<<_lat<<" "<<_long<<endl;
                        
            
           // string phpheader = uploader.send(headerphp, keys,vals,WEB_POST);
            
            //string phpheader = uploader.send("http://12deadpixels.99k.org/header.php", keys,vals,WEB_POST);
          //  cout << "post responseHeader : \n" << phpheader << endl;
            
           // string phpfooter = uploader.send(footerphp, keys,vals,WEB_POST);
			//cout << "post responseFooter : \n" << phpfooter << endl;

            
        }else{
            cout<<"NEXT SCENE";
        scenes[sceneIndex]->stop(); 
        nextScene();
        }
    }
}
void manager::touch(ofPoint touch){
    scenes[sceneIndex]->touch(touch);
}
void manager::nextScene(){
    if(sceneIndex<scenes.size()-1){
        sceneIndex++;
        if (sceneIndex==4) {
            vector<string> keys;
            vector<string>vals;
            
            /*for(int i=0;i<lats.size();i++){
                keys.push_back("lat");
                vals.push_back(ofToString(lats[i]));
                keys.push_back("longI");
                vals.push_back(ofToString(longs[i]));
                keys.push_back("dB_low");
                vals.push_back(ofToString(audioLevels[i]));
            }*/
            for(int i=0;i<lats.size();i++){
                keys.push_back("lat_"+ofToString(i));
                vals.push_back(ofToString(lats[i]));
                keys.push_back("longI_"+ofToString(i));
                vals.push_back(ofToString(longs[i]));
                keys.push_back("dB_low_"+ofToString(i));
                vals.push_back(ofToString(audioLevels[i]));
            }

            cout<<"length of array "<< vals.size()<<" end length of array\n";
            string response = uploader.send(uploadphp, keys,vals,WEB_POST);
            cout << "post responseUploader :  \n" << response << endl;
            scenes[sceneIndex]->start(lats,longs,audioLevels);
        }
        else{
        scenes[sceneIndex]->start();
        }
    }
    else{
        cout<<"this is the last scene, cannot go forward"<<endl;
        
        ///maybe write to server here.
        
                //add data to array and send here
        //string response = uploader.send(uploadphp, keys,vals,WEB_POST);
        //    cout << "post responseUploader :  \n" << response << endl;

        start();

    }
}
void manager::previousScene(){
    if(sceneIndex>=0){
        sceneIndex--;
    }
    else{
        cout<<"this is the first scene, cannot go back"<<endl;
    }
}
void manager::goToScene(int _sceneIndex){
    if (sceneIndex>=0&&sceneIndex<scenes.size()-1) {
        sceneIndex=_sceneIndex;
        scenes[sceneIndex]->start();
    }
    else{
        cout<<"scene "<<_sceneIndex<<"is out of bounds:";
    }
    
}
void manager::stop(){
    
}
void manager::draw(){
    scenes[sceneIndex]->draw();

}
bool manager::getIsRecording(){
    return isRecording;
}
bool manager::getIsListening(){
    return isListening;
}
bool manager::getPageOpened(){
    return pageOpened;
}
void manager::setWasQuiet(bool _wasQuiet){
    wasQuiet=_wasQuiet;
}
void manager::addAudioLevel(float level){
    audioLevelsOneLocation.push_back(level);
}
void manager::setPageOpened(bool _pageOpened){
    pageOpened = _pageOpened;
}