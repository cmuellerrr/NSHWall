/*
 * A class representing tiles shown on the grid.  They hold the basic information
 * that is presented by the wall such as title and featured image.  They 
 * also have an expanded version of themselves.
 */

#include "wall.h"
#include "gridTile.h"

/*
 * Create a tile with the given logical posion and size.  The actual position and
 * size are determined based off of the static variables created in the wall class.
 * You may also specity if tiles are clickable or not.
 */
gridTile::gridTile() {
	set(ofRandom(1000), "", "", ofRectangle(0, 0, 0, 0), true);
}

gridTile::gridTile(int id, string title) {
	set(id, title, "", ofRectangle(0, 0, 0, 0), true);
}
		
gridTile::gridTile(int id, string title, string content) {
	set(id, title, content, ofRectangle(0, 0, 0, 0), true);
}
		
gridTile::gridTile(int id, string title, ofRectangle gridRect) {
	set(id, title, "", gridRect, true);
}
	
gridTile::gridTile(int id, string title, ofRectangle gridRect, bool clickable) {
	set(id, title, "", gridRect, clickable);
}

gridTile::gridTile(int id, string title, string content, ofRectangle gridRect) {
	set(id, title, content, gridRect, true);
}
		
gridTile::gridTile(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	set(id, title, content, gridRect, clickable);
}

gridTile::~gridTile() {
	
}

/*
 * Do the actual work for setting up the tile.
 */
void gridTile::set(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	state = HIDDEN;
	this->id = id;
	this->title = title;
	this->gridRect = gridRect;
	this->clickable = clickable;

	setupTileRect();
	defaultPosition = ofPoint(tileRect.x, tileRect.y);
	offscreenPosition = ofPoint(tileRect.x, -ofGetWindowHeight());
	
	expanded = expandedTile(id, title, content);
}

/*
 * Draw the tile.
 */
void gridTile::draw() {
	if (state != HIDDEN) {
		ofPushStyle();

		if (featuredImg.isAllocated()) {
			featuredImg.draw(tileRect);
		} else {
			ofFill();
			ofRect(tileRect);
		}

		ofPopStyle();
	}
}

/*
 * Handle all input.  Return if something happened.
 */

bool gridTile::mousePressed(int x, int y, int button) {
	if (clickable && tileRect.inside(x, y)) {
		expanded.setState(ENTER);
		return true;
	}
	return false;
}

/*
 * Check for any state transitions based on the tile's
 * current state.  If found, update the tile's current state.
 */
void gridTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(ACTIVE);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

/*
 * Set the tile's state.
 * The animation objects are getting allocated to the heap so make sure they get deleted when done.
 */
void gridTile::setState(int newState) {
	std::cout<<"Setting tile ("<<id<<") state to "<<newState<<'\n';
	switch (newState) {
		case ENTER:
			//Move the tile off screen
			tileRect.setPosition(offscreenPosition);
			animations.push_front(new pointAnimation(&tileRect.position, defaultPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
		case EXIT:
			animations.push_front(new pointAnimation(&tileRect.position, offscreenPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
	}	
	state = newState;
}

/*
 * Set the tile's expandedTile content.
 */
void gridTile::setContent(string content) {
	expanded.setContent(content);
}

/*
 * Set the tile's featured image.  This image
 * then gets pushed to the expanded tile.
 */
void gridTile::setFeaturedImage(string url) {
	ofImage img;

	if (img.loadImage(url)) {
		setFeaturedImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

/*
 * Set the tile's featured image.  This image
 * then gets pushed to the expanded tile.
 */
void gridTile::setFeaturedImage(ofImage img) {
	featuredImg = img;
	addImage(img);
}

/*
 * Add the given image to the expanded tile.
 */
void gridTile::addImage(string url) {
	ofImage img;
	if (img.loadImage(url)) {
		expanded.addImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

/*
 * Add the given image to the expanded tile.
 */
void gridTile::addImage(ofImage img) {
	expanded.addImage(img);
}