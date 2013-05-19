#pragma once

#include "ofMain.h"
#include "paperclip.h"
#include "ofxUI.h"
#include "fft.h"

#define MAX_N_COPIAS 90
#define BUFFER_SIZE 256
#define NUM_WINDOWS 80


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void removeCopia(int copi);
    void addCopia();
    void setupCopia(int copia, int nImage, string shad);
    
    void loadSet(int set);
    void loadShaders();
    void advanceOne(int which);
    ofTrueTypeFont font;
    vector <paperclip> copias;
    vector <ofImage> images;
    vector <string> imagePaths;
    vector <string> shaderFiles;
    vector<ofPoint> animationRefs;
    vector<bool> animationsLoaded;

    
   
    int set=0;
    int nImage=0;
    int nShader=0;
    int select=0;
     string infoarray = "";
    ofTrueTypeFont  rooom;
    
 //FFT
    ofSoundStream soundStream;
    void audioReceived 	(float * input, int bufferSize, int nChannels); 
    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];


};
