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
float wall::ASPECT_RATIO;
//NOTE: these tile values include the margin, so they need to be
//accounted for when creating tiles.
float wall::TILE_W;
float wall::TILE_H;

/*
 * Setup the wall.  Initialize the Fenster canvas and set the static
 * variables and helper objects.
 */
void wall::setup(){
    
    ASPECT_RATIO = 16.0f/9.0f;
    
	// setup a canvas comprised of three columns in two rows, with the
    // resolutions automatically detected from the displays.
    //canvas.setup(this, 3, 2);
    // or, if you want to force the resolutions of the screens:
    //canvas.setup(this, 2, 1, 640, 480);
    // and, if you want to force the resolutions of the screens, and put them
    // all on one display (eg. for testing):
	ofxDisplay * display = ofxDisplayManager::get()->getDisplays().front();
    canvas.setup(this, SCREENS, 1, 1280 / 3, ASPECT_RATIO * 1280 / 3, display);
	
	SCREEN_W = canvas.getWidth() / SCREENS;
	SCREEN_H = canvas.getHeight();
	GROUP_W = SCREEN_W - (MARGIN_GROUP * 2);
	GROUP_H = SCREEN_H - (MARGIN_GROUP * 2);
	TILE_W = GROUP_W / COLUMNS;
	TILE_H = GROUP_H / ROWS;
    
    int count = 0;
    for (list<ofxScreen *>::iterator it = canvas.screens.begin(); it != canvas.screens.end(); it++) {
        ofxScreen * s = &**it;
        s->window->setWindowPosition(10 + (SCREEN_W + 10) * count++, 0);
        s->window->setBorder(false);
    }

	//Get some test routines
	manager.addRoutine(routineFactory::getTestRoutine());
	manager.addRoutine(routineFactory::getTestRoutine());
	manager.addRoutine(routineFactory::getTestRoutine());
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
void wall::keyPressed(int key){
	manager.keyPressed(key);
}

void wall::keyReleased(int key){

}

void wall::mouseMoved(int x, int y ){
	manager.mouseMoved(x, y);
}

void wall::mouseDragged(int x, int y, int button){
	manager.mouseDragged(x, y, button);
}

void wall::mousePressed(int x, int y, int button){
	manager.mousePressed(x, y, button);
}

void wall::mouseReleased(int x, int y, int button){
	manager.mouseReleased(x, y, button);
}

void wall::windowResized(int w, int h){

}

void wall::gotMessage(ofMessage msg){

}

void wall::dragEvent(ofDragInfo dragInfo){ 

}