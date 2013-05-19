#include "testApp.h"
#include "paperclip.h"
//--------------------------------------------------------------
void testApp::setup(){
    
// clip = new paperclip();
    ofSetFrameRate(30);
    
    //    ofShader shader;
//    shader.load("shaders/transparento");
    rooom.loadFont("rooom.ttf", 50, true, true);
	rooom.setLineHeight(18.0f);
	rooom.setLetterSpacing(1.037);
    
    ///CARGAR directorio imagenes
    ofDirectory dir;

    int nFiles = dir.listDir("images");
    copias.assign(20, paperclip());
    if(nFiles) {
        
   //CADA DIRECTORIO
        for(int i=0; i<dir.numFiles(); i++) {
            
            // add the image to the vector
            string filePath = dir.getPath(i);
            ofFile file = dir.getFile(i);
            
            if(file.isDirectory()){
            
                ofDirectory dirTemp;
                int nFiles = dirTemp.listDir(filePath);
                //dirTemp.listDir(filePath);
                //LOCALIZA EN ARRAY DE IMAGENES LAS POSICIONES DE CADA FOLDER
                animationRefs.push_back(ofVec3f(imagePaths.size(), imagePaths.size()+nFiles-1, nFiles));
                animationsLoaded.push_back(bool());
                animationsLoaded.back()=false;
                
                for(int d=0; d<dirTemp.numFiles(); d++) {
                                            
                        string filePatht = dirTemp.getPath(d);
                    //CARGA LAS IMAGENES
                       images.push_back(ofImage());
                      images.back().loadImage(filePatht);
                    //METE EN ARRAY LOS PATHS
                    imagePaths.push_back(filePatht);
                 //   infoarray+=ofToString(filePatht)+" "+ofToString(i)+" "+ofToString(d)+" "+"\n";
                  }
                
                
            }else{
            //images.push_back(ofImage());
            //images.back().loadImage(filePath);
            }
            
            
        }
        
    }
    //setupCopia(1,1,"shaders/transparento");
   // setupCopia(0,0, "shaders/slito");
    //addCopia(15);
    loadShaders();
    loadSet(0);
    copias[0].setup(images[0], "shaders/transparento");
    copias[1].setup(images[1], "shaders/blinko");
    
    //SOUND
	srand((unsigned int)time((time_t *)NULL));
	
	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
	
	//soundStream.setup(0,2,this, 44100,BUFFER_SIZE, 4);
    soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);
	left = new float[BUFFER_SIZE];
	right = new float[BUFFER_SIZE];
    
	for (int i = 0; i < NUM_WINDOWS; i++)
	{
		for (int j = 0; j < BUFFER_SIZE/2; j++)
		{
			freq[i][j] = 0;
		}
	}
    soundStream.start();
    ofSetColor(0x666666);
}
void testApp::loadShaders(){
    string path = "shaders";
    ofDirectory dir(path);
    //only show png files
    dir.allowExt("frag");
    //populate the directory object
    dir.listDir();
    
    //go through and print out all the shaders
    for(int i = 0; i <= dir.numFiles(); i++){
        ofFile file=dir.getFile(i);
        shaderFiles.push_back(file.getBaseName());
        ofLogNotice(file.getBaseName());
       // ofSplitString(dir.getPath(i), dir.getPath(i));
        
    }


}
void testApp::setupCopia(int copia, int nImage, string shad){
   copias[copia].setup(images[nImage], shad);
    
    

}

void testApp::addCopia(){
    copias.push_back(paperclip());
    
   

}
void testApp::loadSet(int set){
    
    int total= animationRefs[set].y-animationRefs[set].x;
    for(vector<string>::iterator it = imagePaths.begin()+animationRefs[set].x; it != imagePaths.begin()+animationRefs[set].y; ++it){
                        images.push_back(ofImage());
                       images.back().loadImage(*it);
    }
      animationsLoaded[set]=true;
    
    
}
void testApp::removeCopia(int copi){
    //copias.erase(copias.begin()+copi);
    
    
}


//-----------------------------------------------   ---------------
void testApp::update(){
    Tweener.update();
    for(vector<paperclip>::iterator it = copias.begin(); it != copias.end(); ++it){
        (it)->update();
    }
    

   
}

//--------------------------------------------------------------
void testApp::draw(){
  //  ofBackground(50, 50, 50);
//    ofBackground(80,80,20);
    ofBackgroundGradient( ofColor(180), ofColor(0), OF_GRADIENT_CIRCULAR);
   // ofSetColor(245, 58, 135);
   ofColor color = ofColor(100,100,100);
    //int temp=animationRefs[set].x+ofRandom(animationRefs[set].y-animationRefs[set].x);
    for(vector<paperclip>::iterator it = copias.begin(); it != copias.end(); ++it){
        if((it)->alive){
        (it)->draw(color);
        }
    }
    //SOUND
    static int index=0;
	float avg_power = 0.0f;
    
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
	
	/* start from 1 because mag[0] = DC component */
	/* and discard the upper half of the buffer */
	for(int j=1; j < BUFFER_SIZE/2; j++) {
		freq[index][j] = magnitude[j];
	}
	
	/* draw the FFT */
	for (int i = 1; i < (int)(BUFFER_SIZE/2); i++){
        ofLine(200+(i*8),400,200+(i*8),400-magnitude[i]*10.0);
		ofLine(200+(i*8),400,200+(i*8),400+magnitude[i]*10.0);
        //int sl = ofMap( magnitude[i]*10.0, 0, 500, 0, animationRefs[set].z);
        
        
     //   cout <<"  "<< magnitude[i]*10.0 << " " ;
//        if (magnitude[i]) {
//            statements
//        }
	}
    if (magnitude[20]*10>50) {
        advanceOne(select);
    }
    
    
	///INFO
    string info = infoarray;
	info += "Press [1] select- ["+ofToString(select)+"]\n";
	info += "Press [0] set+ ["+ofToString(set)+"]\n";

	info += "GLITCHY?: "+ofToString(copias[select].glitch)+"\n";
    info +="SETIMAGES FROM: "+ofToString(animationRefs[set].x)+" TO: "+ofToString(animationRefs[set].y)+"\n";
    info +="nSetImages: "+ofToString(animationRefs[set].z)+"\n";
    info += "NIMage "+ofToString(nImage)+"\n";

    info += "IMAGE "+ofToString(imagePaths[animationRefs[set].x+nImage])+"\n";
    info += "nShader "+ofToString(nShader)+"\n";

    info += "SHADER "+ofToString(shaderFiles[nShader])+"\n\n";
    ofSetHexColor(0x000000);
    ofRect(10, 10, 250, 150);
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString(info, 30, 30);
    rooom.drawString("", 300, 350);
   }

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key=='d' ){
        copias[select].setShader("shaders/"+shaderFiles[nShader]);
        cout << select;

    };
    if( key=='s' ){
        copias[select].setShader("shaders/transpativo");
        cout << select;
    };
    if( key=='l' ){
        
        loadSet(set);
       
    };
       if( key=='c' ){
         int temp=animationRefs[set].x+ofRandom(animationRefs[set].y-animationRefs[set].x);
           setupCopia(select, temp , "shaders/transparento");
           //copias[select].setPos(ofGetMouseX()  ,ofGetMouseX(),3,1);
           cout << copias.size();
       
    };
    if( key=='v' ){
        copias[select].scaleX=ofRandom(5.0);
        
    };
    if( key=='f' ){
        set=max(set-1, 0);
        
        cout << set;
         nImage=0;
    };
  
    if( key=='h' ){
        cout << animationRefs.size() ;
         set=min(set+1, int(animationRefs.size()-1));
        if (!animationsLoaded[set]) {
            loadSet(set);
            
        }
         //cout << min(set, );
        
         nImage=0;
        //nImage++;
    };
    if( key=='1' ){
        select++;
         cout << select;
        
    };
    if( key=='0' ){
        select--;
         cout << select;
//        cout << max(copias.size(), select);
//
    };
    if( key=='b' ){
        copias[select].glitch=true;
        //        cout << max(copias.size(), select);
        //
    };
    if( key=='n' ){
        copias[select].glitch=false;
        //        cout << max(copias.size(), select);
        //
    };
    if( key=='z' ){
        
        nShader=int(nShader+1)%int(shaderFiles.size()-1);
      //  nShader++;
        //        cout << max(copias.size(), select);
        //
    };
    if( key=='x' ){
        
        nShader=max(int(nShader-1), 0);
        //        cout << max(copias.size(), select);
        //
    };
    if( key=='p' ){
        ofSaveFrame();
        //        cout << max(copias.size(), select);
        //
    };
    if( key=='g' ){
        //int temp=animationRefs[set].x+ofRandom(animationRefs[set].y-animationRefs[set].x);
        advanceOne(select);

    };
}
void testApp:: advanceOne(int which){
    nImage = int(nImage+1)%int(animationRefs[set].z);
    copias[which].setImage(images[animationRefs[set].x+nImage]);
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    copias[select].setPos(ofGetMouseX()  , ofGetMouseY(),3,1);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
	bufferCounter++;
}