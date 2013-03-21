/*
 *
 * Class representing the overall wall application.  Sets up some static 
 * variables regarding the environment before initializing the other helper
 * objects.
 *
 */

#include "wall.h"
#include "routineFactory.h"

//Need to define the static variables in global scope.
float wall::SCREEN_W;
float wall::SCREEN_H;
float wall::GROUP_W;
float wall::GROUP_H;
//NOTE: these tile values include the margin, so they need to be
//accounted for when creating tiles.
float wall::TILE_W;
float wall::TILE_H;

/*
 * Setup the wall.  Initialize the Fenster canvas and set the static
 * variables and helper objects.
 */
void wall::setup(){
	// setup a canvas comprised of three columns in two rows, with the
    // resolutions automatically detected from the displays.
    //canvas.setup(this, 3, 2);
    // or, if you want to force the resolutions of the screens:
    //canvas.setup(this, 2, 1, 640, 480);
    // and, if you want to force the resolutions of the screens, and put them
    // all on one display (eg. for testing):
	ofxDisplay * display = ofxDisplayManager::get()->getDisplays().front();
    canvas.setup(this, SCREENS, 1, 640, 1024, display);

	SCREEN_W = canvas.getWidth() / SCREENS;
	SCREEN_H = canvas.getHeight();
	GROUP_W = SCREEN_W - (MARGIN_GROUP * 2);
	GROUP_H = SCREEN_H - (MARGIN_GROUP * 2);
	TILE_W = GROUP_W / COLUMNS;
	TILE_H = GROUP_H / ROWS;

	//Get some test routines
	manager.addRoutine(routineFactory::getTestRoutine(111));
	manager.addRoutine(routineFactory::getTestRoutine(222));
	manager.addRoutine(routineFactory::getTestRoutine(333));
}

/*
 * Update the wall.  Just route to the routine manager.
 */
void wall::update(){
	manager.update();
}

/*
 * Draw the wall.  We need to setup the perspective for 
 * the fenster windows before drawing the application.
 */
void wall::draw(){
	canvas.setupPerspectiveForActiveScreen();

	ofPushStyle();
    {
		manager.draw();
	}
    ofPopStyle();
}

/*
 * Handle input to the application.  We'll comment these in classes where it 
 * actually has some kind of logic and doesn't just route to another class.
 */
void wall::keyPressed(int key, ofxFenster* f){
	manager.keyPressed(key, getWindowIndex(f));
}

void wall::keyReleased(int key, ofxFenster* f){

}

void wall::mouseMoved(int x, int y, ofxFenster* f){
	manager.mouseMoved(x, y, getWindowIndex(f));
}

void wall::mouseDragged(int x, int y, int button, ofxFenster* f){
	manager.mouseDragged(x, y, button, getWindowIndex(f));
}

void wall::mousePressed(int x, int y, int button, ofxFenster* f){
	manager.mousePressed(x, y, button, getWindowIndex(f));
}

void wall::mouseReleased(int x, int y, int button, ofxFenster* f){
	manager.mouseReleased(x, y, button, getWindowIndex(f));
}

void wall::windowResized(int w, int h, ofxFenster* f){

}

void wall::gotMessage(ofMessage msg){

}

void wall::dragEvent(ofDragInfo dragInfo){ 

}

//Determine the window index based off of the provided fenster.
//We are only returning the x portion of the index right now, but if
//the wall were to change to multiple dimensions of screens, then 
//we can deal with the index object.
int wall::getWindowIndex(ofxFenster* f) {
	for (list<ofxScreen*>::iterator it = canvas.screens.begin(); it != canvas.screens.end(); it++) {
		if((*it)->window == f) return (*it)->index.x;
	}
	return -1;
}