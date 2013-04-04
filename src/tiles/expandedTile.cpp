/*
 * A class representing the expanded version of an article tile.
 * The tiles expand from the top left corner to show the full article 
 * contents and their related media.
 */

#include "wall.h"
#include "expandedTile.h"

/*
 * Create the tile with the given parameters.  Every constructor
 * calls the 'set' function with default parameters if not required by 
 * the constructor.
 */
expandedTile::expandedTile() {
	set(ofRandom(1000), "", "");
}

expandedTile::expandedTile(int id, string title) {
	set(id, title, "");
}

expandedTile::expandedTile(int id, string title, string content) {
	set(id, title, content);
}

expandedTile::~expandedTile() {
	//TODO clean up animations and images
}

/*
 * Do the actual work for creating the expanded tile.
 */
void expandedTile::set(int id, string title, string content) {
	state = HIDDEN;
	this->id = id;
	this->title = title;
	this->content = content;

	translateGridDimensions();
}


/*
 * Draw the tile.
 */
void expandedTile::draw() {
	if (state != HIDDEN) {
		ofPushStyle();
	
		ofSetColor(ofColor(128, 128, 128));
		ofFill();
		ofRect(tileRect);

		ofPopStyle();
	}
}

/*
 * If clicked, set to exit.
 */
bool expandedTile::mousePressed(int x, int y, int button) {
	if (state == ACTIVE && tileRect.inside(x, y)) {
		setState(EXIT);
		return true;
	}
	return false;
}

/*
 * Check for any state transitions based on the tile's
 * current state.  If found, update the tile's current state.
 */
void expandedTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(ACTIVE);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

/*
 * Set the featured tile's state.
 * The animation objects are getting allocated to the heap so make sure they get deleted when done.
 */
void expandedTile::setState(int newState) {
	std::cout<<"Setting feature ("<<id<<") state to "<<newState<<'\n';
	switch (newState) {
		case ENTER:
			animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, defaultSize, .3, BOUNCY));
			break;
		case EXIT:
			animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, ofPoint(0, 0), .3, BOUNCY));
			break;
	}
	state = newState;	
}

/*
 * Add the given image to the tile's list.
 */
void expandedTile::addImage(ofImage img) {
	images.push_back(img);
}

/*
 * Set up the tile rectangle based on the grid
 * rectangle.  Basically, translate the grid dimensions
 * into pixel dimensions.  Also set the default position
 * and offscreen position.
 */
void expandedTile::translateGridDimensions() {
	int x = (wall::TILE_W / 2) + MARGIN_TILE;
	int y = (wall::TILE_H * 0.75) + MARGIN_TILE;
	int w = (wall::SCREEN_W * 0.75) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * (ROWS - 2));

	tileRect = ofRectangle(x, y, 0, 0);
	defaultPosition = ofPoint(tileRect.x, tileRect.y);
	offscreenPosition = ofPoint(tileRect.x, -ofGetWindowHeight());
	defaultSize = ofPoint(w, h);
}