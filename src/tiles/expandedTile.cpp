#include "wall.h"
#include "expandedTile.h"

/*
 * Create an expaned version of a normal tile.
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
	
}

/*
 * Do the actual work for creating the expanded tile.
 */
void expandedTile::set(int id, string title, string content) {
	state = HIDDEN;
	this->id = id;
	this->title = title;
	this->content = content;

	int x = (wall::TILE_W / 2) + MARGIN_TILE;
	int y = (wall::TILE_H * 0.75) + MARGIN_TILE;
	int w = (wall::SCREEN_W * 0.75) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * (ROWS - 2));

	finalSize = ofPoint(w, h);
	tileRect = ofRectangle(x, y, 0, 0);
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
 * Handle all input.  Return if something happened.
 */

        
bool expandedTile::mousePressed(int x, int y, int button) {
	if (tileRect.inside(x, y)) {
		setState(EXIT);
	}
	return false;
}

void expandedTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(ACTIVE);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

/*
 * Return if the tile is, or will be, animating.
 */
bool expandedTile::isAnimating() {
	return !animations.empty();
}

/*
 * Add the given image to the tile's list.
 */
void expandedTile::addImage(ofImage img) {
	images.push_back(img);
}

/*
 * Set the featured tile's state.
 * The animation objects are getting allocated to the heap so make sure they get deleted when done.
 */
void expandedTile::setState(int newState) {
	std::cout<<"Setting feature ("<<id<<") state to "<<newState<<'\n';
	switch (newState) {
		case ENTER:
			animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, finalSize, .3, BOUNCY));
			break;
		case EXIT:
			animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, ofPoint(0, 0), .3, BOUNCY));
			break;
	}
	state = newState;	
}

void expandedTile::setContent(string newContent) {
	content = newContent;
}