//
//  paperclip.cpp
//  newglsl
//
//  Created by Sergio Millan on 10/05/13.
//
//

#include "paperclip.h"
#include "ofMain.h"



void paperclip::setup(ofImage img, string shaderFile){
//    SHADER
    shader.load(shaderFile);
//    IMAGE
    image=img;
    ofFbo ping, pong, fbo1;
    width=image.getWidth();
    height=image.getHeight();
    
//  PINGOPONGO
    ping.allocate(width,height,GL_RGBA);
    pong.allocate(width,height,GL_RGBA);
    fbo1.allocate(width,height,GL_RGBA);
    pingpong.push_back(ping);
    pingpong.push_back(pong);
    pingpong.push_back(fbo1);
    read=0;
    write=1;
    ofEnableAlphaBlending();
    alive=true;
    if (!glitch) {
        pingpong[2].begin();
        //ofSetColor(255);
        image.draw(0, 0);
        pingpong[2].end();
        pingpong[0].begin();
        //ofSetColor(255);
        image.draw(0, 0);
        pingpong[0].end();
    }
   
}

void paperclip:: update(){
    
    int temp = write;
    write = read;
    read = temp;
    



}

void paperclip::setImage(ofImage img){
  //  ofFbo ping, pong, fbo1;
    image=img;
    width=image.getWidth();
    height=image.getHeight();
    if (!glitch) {
    pingpong[2].allocate(width,height,GL_RGBA);
    pingpong[0].allocate(width,height,GL_RGBA);
    pingpong[1].allocate(width,height,GL_RGBA);
    pingpong[0].begin();
        	ofSetColor(255);
            image.draw(0, 0);
     pingpong[0].end();
        pingpong[2].begin();
        ofSetColor(255);
        image.draw(0, 0);
        pingpong[2].end();
        
    }else{
        pingpong[2].allocate(width,height,GL_RGBA);
        pingpong[0].allocate(width,height,GL_RGBA);
        pingpong[1].allocate(width,height,GL_RGBA);
        pingpong[0].begin();
        ofSetColor(255);
        image.draw(0, 0);
        pingpong[0].end();
    
    }
    

};
void paperclip::setShader(string shaderFile){
   // cout << shaderFile ;
     shader.load(shaderFile);
    
}
void paperclip::clearFbo(){
    pingpong[2].begin();
    ofClear(0, 0, 0, 1);
    pingpong[2].end();
};

void paperclip:: setPos(float x, float y, float xvel, float yvel){
    Tweener.addTween(position.x, x, xvel, &ofxTransitions::easeOutSine);
    Tweener.addTween(position.y, y,  yvel, &ofxTransitions::easeOutSine);

}

void paperclip::setParams(float par1, float par2, float par3){



}
void paperclip::draw(ofColor color){
    pingpong[write].begin();
	ofClear(0, 0, 0, 1); // we clear the fbo.
	
	shader.begin();
    // shader begin: set values.
    shader.setUniformTexture("src_tex_unit0",   pingpong[read], 0 );
    shader.setUniformTexture("original",   pingpong[2], 1 );
    shader.setUniform2f("dest_tex_size", width, height);
    shader.setUniform1f("timer", ofGetFrameNum());
    shader.setUniform1f("par1", ofGetFrameNum());
    shader.setUniform1f("par2", ofGetFrameNum());
    
    shader.setUniform3i("color", color.r, color.g, color.b);
    glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    
    glTexCoord2f(width, 0); glVertex3f(width, 0, 0);
	glTexCoord2f(width, height); glVertex3f(width, height, 0);
	glTexCoord2f(0,height);  glVertex3f(0,height, 0);
	glEnd();
    
    shader.end(); // shader's end.
	
	
    pingpong[write].end(); // end of the "containing" fbo.
    glPushMatrix();
   
    ofEnableNormalizedTexCoords();
    shader;
  

   
    ofScale(scaleX, scaleX);
    pingpong[write].draw(position.x,position.y);
    glPopMatrix();




}