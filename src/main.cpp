#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1452, 764, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
    ofSetFrameRate(2);
    ofSetWindowTitle("isehgisug");
}
