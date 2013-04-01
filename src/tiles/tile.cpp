/*
 * A class representing tiles in their simplest form.  
 * Pretty much just a box with an id.  This class was written 
 * to be subclassed to tailor tile behavior to the type of 
 * information being presented.
 */

#include "wall.h"
#include "tile.h"

/*
 * Create a tile with the given logical posion and size.
 * You may also specity if tiles are clickable or not.
 */
tile::tile() {
	set(ofRandom(1000), ofRectangle(0, 0, 1, 1), true);
}

tile::tile(int id, ofRectangle gridRect) {
	set(id, gridRect, true);
}
	
tile::tile(int id, ofRectangle gridRect, bool clickable) {
	set(id, gridRect, clickable);
}


tile::~tile() {
	
}

/*
 * Do the actual work for setting up the tile.
 */
void tile::set(int id, ofRectangle gridRect, bool clickable) {
	state = HIDDEN;
	this->id = id;
	this->gridRect = gridRect;
	this->clickable = clickable;

	setupTileRect();
	defaultPosition = ofPoint(tileRect.x, tileRect.y);
	offscreenPosition = ofPoint(tileRect.x, -ofGetWindowHeight());
}

/*
 * Update the tile.  We really only care if it is animating.
 * Update any animations it has, and remove any that are done.
 * Afterwards, check for any state transitions.
 */
void tile::update() {
	if (state != HIDDEN) {
		//This is a little different because we are removing things while traversing
		for (list<animation*>::iterator it = animations.begin(); it != animations.end();) {
			if ((*it)->isDone()) {
				delete *it;
				it = animations.erase(it);
			}
			else {
				(*it)->update();
				++it;
			}
		}
		checkStateTransition();
	}
}

/*
 * Draw the tile.
 */
void tile::draw() {
	if (state != HIDDEN) {
		ofPushStyle();

		ofFill();
		ofRect(tileRect);

		ofPopStyle();
	}
}

/*
 * Handle all input.  Return if something happened.
 */

bool tile::mouseMoved(int x, int y)  {
	return false;
}

bool tile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool tile::mousePressed(int x, int y, int button) {
	return clickable && tileRect.inside(x, y);
}
        
bool tile::mouseReleased(int x, int y, int button) {
	return false;
}

/*
 * Check for any state transitions based on the tile's
 * current state.  If found, update the tile's current state.
 */
void tile::checkStateTransition() {
	//No op for the base class
}

/*
 * Return if the tile is, or will be, animating.
 */
bool tile::isAnimating() {
	return !animations.empty();
}

/*
 * Set up the tile rectangle based on the grid
 * rectangle.  Basically, translate the grid dimensions
 * into pixel dimensions.
 */
void tile::setupTileRect() {
	int x = (wall::TILE_W * gridRect.x) + MARGIN_TILE;
	int y = (wall::TILE_H * gridRect.y) + MARGIN_TILE;
	int w = (wall::TILE_W * gridRect.width) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * gridRect.height) - (MARGIN_TILE * 2);

	tileRect = ofRectangle(x, y, w, h);
}