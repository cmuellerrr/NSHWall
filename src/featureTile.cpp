#include "wall.h"
#include "featureTile.h"

/*
 *
 */
featureTile::featureTile() {
	mode = HIDDEN;

	int x = (wall::TILE_W / 2) + MARGIN_TILE;
	int y = (wall::TILE_H * 0.75) + MARGIN_TILE;
	int w = (wall::SCREEN_W * 0.75) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * (ROWS - 2));

	finalSize = ofPoint(w, h);
	tileRect = ofRectangle(x, y, w, h);

	//We are hacking this point to represent the width and height
	size.setPosition(ofPoint(0, 0));
}

featureTile::~featureTile() {
	
}


/*
 * Update the tile.  We really only care if it is animating.
 */
void featureTile::update() {
	if (size.isOrWillBeAnimating()) {
		size.update(1.0f / ofGetFrameRate());
		tileRect.setWidth(size.getCurrentPosition().x);
		tileRect.setHeight(size.getCurrentPosition().y);
	}
	if (mode == EXIT && size.hasFinishedAnimating()) mode = HIDDEN;
}

/*
 * Draw the tile.
 */
void featureTile::draw() {
	ofPushStyle();
	
	ofSetColor(ofColor(128, 128, 128));
	ofFill();
	ofRect(tileRect);

	ofPopStyle();
}

/*
 * Handle all input.  Return if something happened.
 */

bool featureTile::mouseMoved(int x, int y)  {
	return false;
}

bool featureTile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool featureTile::mousePressed(int x, int y, int button) {
	if (tileRect.inside(x, y)) {
		cout<<"HIT at "<<x<<" "<<y<<"\n"; 
		setMode(EXIT);
	}
	return false;
}
        
bool featureTile::mouseReleased(int x, int y, int button) {
	return false;
}

/*
 * Return if the tile is, or will be, animating.
 */
bool featureTile::isAnimating() {
	return size.isOrWillBeAnimating();
}


/*
 * Set up the tile's entrance to the wall.
 */
void featureTile::setupEntrance() {
	//Move the tile off screen
	//position.setPosition(getOffscreenPosition(edge));
	
	//Animate to the desired position
	size.animateTo(finalSize);
	size.setDuration(.3);
	size.setRepeatType(PLAY_ONCE);
	size.setCurve(BOUNCY);
}

/*
 * Set up the tile's exit from the wall.
 */
void featureTile::setupExit() {
	//Animate to its offscreen position
	size.animateTo(ofPoint(0, 0));
	size.setDuration(.3);
	size.setRepeatType(PLAY_ONCE);
	size.setCurve(BOUNCY);
}

void featureTile::setMode(int newMode) {
	std::cout<<"Setting feature mode to "<<newMode<<'\n';
	mode = newMode;
	switch (mode) {
		case ENTER:
			setupEntrance();
			break;
		case EXIT:
			setupExit();
			break;
	}	
}