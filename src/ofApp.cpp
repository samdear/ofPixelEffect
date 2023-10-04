// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    grabber.setup(1280, 720);
    resultImg.allocate(1280, 720, OF_IMAGE_COLOR);
    
    // Set texture filtering to GL_NEAREST to achieve a pixelated effect
    resultImg.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    blockSize.set("Pixel Size", 1, 1, 50);
    
    parameters.setName("Color Style");
    parameters.add(regChoice.set("Regular", true));
    parameters.add(limitedChoice.set("Limited", false));
    
    // Added listeners to monitor changes in the color style
    regChoice.addListener(this, &ofApp::regChoiceChanged);
    limitedChoice.addListener(this, &ofApp::limitedChoiceChanged);
    
    guiPanel.setup("Effects");
    guiPanel.add(parameters);
    guiPanel.add(blockSize);
}

void ofApp::regChoiceChanged(bool & regular)
{
    ofSetVerticalSync(regChoice);
    ofLogNotice() << "regChoice changed: " << regChoice;
    
    if (regChoice.get() == true)
    {
        limitedChoice.set(false);
    }
    else
    {
        limitedChoice.set(true);
    }
}

void ofApp::limitedChoiceChanged(bool & limited)
{
    ofSetVerticalSync(limitedChoice);
    ofLogNotice() << "limitedChoice changed: " << limitedChoice;
    
    if (limitedChoice.get() == true)
    {
        regChoice.set(false);
    }
    else
    {
        regChoice.set(true);
    }
}

void ofApp::update()
{
    // Update the video effect based on the chosen color style
    if (regChoice == true && limitedChoice == false)
    {
        regColors();
    }
    else
    {
        limitedColors();
    }
}

void ofApp::draw()
{
    int w = 1280;
    int h = 720;
    
    // Create an off-screen frame buffer object (FBO)
    ofFbo fbo;
    
    // Adjust the FBO size for pixelation
    fbo.allocate(w / blockSize, h / blockSize);
    fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    
    // Draw the webcam input to the FBO, scaled for pixelation
    resultImg.draw(0, 0, w / blockSize, h / blockSize);
    
    fbo.end();
    fbo.draw(0, 0, w, h);
    
    guiPanel.draw();
}

void ofApp::regColors()
{
    grabber.update();
    
    ofPixels& grabberPix = grabber.getPixels();
    ofPixels& resultPix = resultImg.getPixels();
    
    // Copy the color information from the webcam image to the result image
    for (int y = 0; y < grabberPix.getHeight(); y++)
    {
        for (int x = 0; x < grabberPix.getWidth(); x++)
        {
            ofColor pixColor = grabberPix.getColor(x, y);
            resultPix.setColor(x, y, pixColor);
        }
    }
    resultImg.update();
}

void ofApp::limitedColors()
{
    grabber.update();
    
    ofPixels& grabberPix = grabber.getPixels();
    ofPixels& resultPix = resultImg.getPixels();
    
    // Replace colors in the result image based on the hue of the webcam image
    for (int y = 0; y < grabberPix.getHeight(); y++)
    {
        for (int x = 0; x < grabberPix.getWidth(); x++)
        {
            ofColor pixColor = grabberPix.getColor(x, y);
            
            int hue = pixColor.getHue();
            
            int numColors = 3;
            int range = 255 / numColors;
            
            // Assign a new color to the result image based on the hue range
            if (abs(hue) < range * 1)
                resultPix.setColor(x, y, ofColor::red);
            else if (abs(hue) < range * 2)
                resultPix.setColor(x, y, ofColor::blue);
            else
                resultPix.setColor(x, y, ofColor::green);
        }
    }
    resultImg.update();
}
