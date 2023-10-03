// ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void selectColors();
    void regColors();
    
    ofVideoGrabber grabber;
    ofImage resultImg;
    
    ofParameter<int> blockSize;
    ofxPanel guiPanel;
};
