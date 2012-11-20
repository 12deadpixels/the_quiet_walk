#include "manager.h"
////////////////////////---------/////////////////////////////////////
void manager::setup(){
    
    scenes.push_back(&wel);
    scenes.push_back(&dir);
    scenes.push_back(&lis);
    scenes.push_back(&end);
    isRecording=false;
    playBack = false;
    
    for(int i=0;i<scenes.size();i++){
        scenes[i]->setup();
    }
    
}
void manager::start(){
    
    cout<<"MANAGER START ";
    sceneIndex=0;
    //tell the direction scene that this is the first run
    scenes[1]->setState(0);
    scenes[sceneIndex]->start();
    numAttempts = 0;
    
}
void manager::update(){
    scenes[sceneIndex]->update();
    if(scenes[sceneIndex]->getSceneHasEnded()){
        cout<<"go to next scene";
        
        //first check if we need to swithc back because we are on the listening scene
        if (sceneIndex==2) {
            bool wasQuiet = scenes[sceneIndex]->getEndState();
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
        scenes[sceneIndex]->start();
    }
    else{
        cout<<"this is the last scene, cannot go forward"<<endl;
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
