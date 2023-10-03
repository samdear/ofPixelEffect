// ofApp.cpp
#include "ofApp.h"

void ofApp::setup()
{
    // Initialize the webcam grabber
    grabber.setup(1280, 720);
    
    // Allocate an image buffer for the result image with the same resolution
    resultImg.allocate(1280, 720, OF_IMAGE_COLOR);
    
    // Set texture filtering to GL_NEAREST to achieve a pixelated effect
    resultImg.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    // Create a GUI panel with a slider for controlling pixelation block size
    blockSize.set("Pixel Size", 1, 1, 50);
    
    guiPanel.setup("Pixels");
    guiPanel.add(blockSize);
}

void ofApp::update()
{
    //Run whichever function you input
    regColors();
}

void ofApp::draw()
{
    int w = 1280;  // Set the output width
    int h = 720;   // Set the output height
    
    // Create an off-screen frame buffer object (FBO)
    ofFbo fbo;
    
    // Adjust the FBO size for pixelation
    fbo.allocate(w / blockSize, h / blockSize);
    
    // Set texture filtering for the FBO to achieve a pixelated effect
    fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    fbo.begin();
    ofClear(0, 0, 0, 0);  // Clear the FBO
    
    // Draw the webcam input to the FBO, scaled for pixelation
    resultImg.draw(0, 0, w / blockSize, h / blockSize);
    
    fbo.end();
    
    // Draw the FBO at full screen size, creating the pixelation effect
    fbo.draw(0, 0, w, h);
    
    // Draw the GUI panel for adjusting pixelation block size
    guiPanel.draw();
}

void ofApp::regColors()
{
    // Update the webcam grabber to get the latest frame
    grabber.update();
    
    // Get a reference to the webcam image and the result image
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
    resultImg.update();  // Update the result image with the new colors
}

void ofApp::selectColors()
{
    // Update the webcam grabber to get the latest frame
    grabber.update();
    
    // Get a reference to the webcam image and the result image
    ofPixels& grabberPix = grabber.getPixels();
    ofPixels& resultPix = resultImg.getPixels();
    
    // Replace colors in the result image based on the hue of the webcam image
    for (int y = 0; y < grabberPix.getHeight(); y++)
    {
        for (int x = 0; x < grabberPix.getWidth(); x++)
        {
            ofColor pixColor = grabberPix.getColor(x, y);
            
            // Calculate the hue value of the pixel
            int hue = pixColor.getHue();
            
            // Define the number of colors and the range for categorizing hues
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
    resultImg.update();  // Update the result image with the new colors
}
