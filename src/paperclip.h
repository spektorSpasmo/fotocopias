//
//  paperclip.h
//  newglsl
//
//  Created by Sergio Millan on 10/05/13.
//
//
#define MAX_N_PTS 190
#include "ofMain.h"
#include "ofxTweener.h"
#ifndef paperclip_h
#define paperclip_h
class paperclip : public ofBaseApp{
private:
    
      
public:
	void setup(ofImage img, string shaderFile);
	void update();
    void setPos(float x, float y, float xvel, float yvel);
	void draw(ofColor color);
    void setShader(string shaderFile);
    void setImage(ofImage img);
    void setScale(float sc);
    void setParams(float par1 , float par2, float par3);
    bool alive=false;
    bool glitch=false;
    void clearFbo();
    int width;
    int height;
    ofPoint position;
    float scaleX=1;
    float scaleY=1;
    ofShader shader;
    
//    ofFbo ping, pong, fbo1;
    int read, write;
    vector<float>parameters;
    vector<ofFbo>pingpong;
    
    ofImage image;


};



#endif
