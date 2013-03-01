#include "ofMain.h"
#include "wall.h"
#include "ofxFensterManager.h"
#include "ofAppGlutWindow.h"

/*
 * Sets up the Fenster manager and runs the wall class.
 * Fenster allows us to split the app up into separate 
 * windows.
 */
int main( ){
	ofSetupOpenGL(ofxFensterManager::get(), 1024, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunFensterApp(new wall());
}
