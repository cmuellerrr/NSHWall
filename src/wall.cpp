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
	SCREEN_W = ofGetWindowWidth() / SCREENS;
	SCREEN_H = ofGetWindowHeight();
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
	manager.draw();
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