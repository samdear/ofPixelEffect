// ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofParameter.h"


class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void limitedColors();
    void regColors();
    
    void regChoiceChanged(bool & regChoice);
    void limitedChoiceChanged(bool & limitedChoice);

    
    ofVideoGrabber grabber;
    ofImage resultImg;
    
    ofParameter<int> blockSize;
    ofParameter<bool> regChoice;
    ofParameter<bool> limitedChoice;
    ofParameterGroup parameters;
    ofxPanel guiPanel;
};
