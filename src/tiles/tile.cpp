/*
 * A class representing tiles in their simplest form.  
 * Pretty much just a box with an id.  This class was written 
 * to be subclassed to tailor tile behavior to the type of 
 * information being presented.
 */

#include "wall.h"
#include "tile.h"


tile::~tile() {
	//TODO clean up animation objects
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
	return tileRect.inside(x, y);
}

bool tile::mouseDragged(int x, int y, int button) {
	return tileRect.inside(x, y);
}
        
bool tile::mousePressed(int x, int y, int button) {
	return tileRect.inside(x, y);
}
        
bool tile::mouseReleased(int x, int y, int button) {
	return tileRect.inside(x, y);
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
 * into pixel dimensions.  Also set the default position
 * and offscreen position.
 */
void tile::translateGridDimensions() {
	int x = (wall::TILE_W * gridRect.x) + MARGIN_TILE;
	int y = (wall::TILE_H * gridRect.y) + MARGIN_TILE;
	int w = (wall::TILE_W * gridRect.width) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * gridRect.height) - (MARGIN_TILE * 2);

	tileRect = ofRectangle(x, y, w, h);
	defaultPosition = ofPoint(tileRect.x, tileRect.y);
	offscreenPosition = ofPoint(tileRect.x, -ofGetWindowHeight());
}