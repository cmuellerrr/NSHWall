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

//--------------------------------------------------------------
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

	manager.addRoutine(routineFactory::getTestRoutine());
	manager.addRoutine(routineFactory::getTestRoutine());
	manager.addRoutine(routineFactory::getTestRoutine());
}

//--------------------------------------------------------------
void wall::update(){
	manager.update();
}

//--------------------------------------------------------------
void wall::draw(){
	canvas.setupPerspectiveForActiveScreen();

	ofPushStyle();
    {
		manager.draw();
	}
    ofPopStyle();
}

//--------------------------------------------------------------
void wall::keyPressed(int key){
	manager.keyPressed(key);
}

//--------------------------------------------------------------
void wall::keyReleased(int key){

}

//--------------------------------------------------------------
void wall::mouseMoved(int x, int y ){
	manager.mouseMoved(x, y);
}

//--------------------------------------------------------------
void wall::mouseDragged(int x, int y, int button){
	manager.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void wall::mousePressed(int x, int y, int button){
	manager.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void wall::mouseReleased(int x, int y, int button){
	manager.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void wall::windowResized(int w, int h){

}

//--------------------------------------------------------------
void wall::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void wall::dragEvent(ofDragInfo dragInfo){ 

}