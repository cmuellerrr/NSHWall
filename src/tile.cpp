#include "wall.h"
#include "tile.h"


tile::tile() {
	
}

tile::tile(float column, float row, float columnSpan, float rowSpan, bool click) {
	
	clickable = click;
	
	gridRect = ofRectangle(column, row, columnSpan, rowSpan);

	int x = (wall::TILE_W * column) + MARGIN_TILE;
	int y = (wall::TILE_H * row) + MARGIN_TILE;
	int w = (wall::TILE_W * columnSpan) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * rowSpan) - (MARGIN_TILE * 2);

	finalPosition = ofPoint(x, y);

	tileRect = ofRectangle(finalPosition, w, h);
}

tile::~tile() {
	
}

void tile::update() {
	if (path.isOrWillBeAnimating()) {
		path.update(1.0f / ofGetFrameRate());
		tileRect.setPosition(path.getCurrentPosition());
	}
}
		
void tile::draw() {
	ofPushStyle();

	ofFill();
	ofRect(tileRect);

	ofPopStyle();
}

bool tile::mouseMoved(int x, int y)  {
	return false;
}

bool tile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool tile::mousePressed(int x, int y, int button) {
	return false;
}
        
bool tile::mouseReleased(int x, int y, int button) {
	return false;
}

bool tile::isAnimating() {
	return path.isOrWillBeAnimating();
}

void tile::setupEntrance() {
	//Move the tile off screen
	path.setPosition(ofPoint(-ofGetWindowWidth(), finalPosition.y));
	
	//Animate to its
	path.animateToAfterDelay(finalPosition, ofRandom(.5));
	path.setDuration(1.5);
	path.setRepeatType(PLAY_ONCE);
	path.setCurve(EASE_IN_EASE_OUT);
}

void tile::setupExit() {
	path.animateToAfterDelay(ofPoint(finalPosition.x, -ofGetWindowHeight()), ofRandom(.5));
	path.setDuration(1.5);
	path.setRepeatType(PLAY_ONCE);
	path.setCurve(EASE_IN_EASE_OUT);
}