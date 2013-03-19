/*
 * A class to represent groups of tiles.  A tile group is essentially 
 * representing one of the wall's screens.  This acts as another manager
 * class.
 */

#include "wall.h"
#include "tileGroup.h"

/*
 * Setup the tile group within the given bounds.
 */
tileGroup::tileGroup(ofRectangle bounds, int i) {
	index = i;
	boundingBox = bounds;

	focus = 0;
	
	tileColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

tileGroup::~tileGroup() {
	
}

/*
 * Update the tile group.  If one of the tiles is focused, then only update
 * that one.
 */
void tileGroup::update() {
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			it->update();
		}
	} else {
		focus->update();
		if (focus->getMode() == HIDDEN) {
			focus = 0;
		}
	}
}

/*
 * Draw the tile group.  If one tile is focused, then draw the expanded version on top of the 
 * overall group.  Make sure to translate to the bounding box so tile draw correctly.
 */
void tileGroup::draw() {
	ofPushMatrix();
	ofTranslate(boundingBox.getPosition());

	ofPushStyle();
	ofSetColor(tileColor);

	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->draw();
	}
	if (focus != 0) focus->draw();

	ofPopStyle();
	ofPopMatrix();
}

/*
 * Handle all input.  Route to the tiles and make note when something happens.
 */

bool tileGroup::mouseMoved(int x, int y)  {
	bool hit = false;
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->mouseMoved(x, y)) hit = true;
		}
	} else {
		focus->mouseMoved(x, y);
	}
	return hit;
}

bool tileGroup::mouseDragged(int x, int y, int button) {
	bool hit = false;
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->mouseDragged(x, y, button)) hit = true;
		}
	} else {
		if (focus->mouseDragged(x, y, button)) hit = true;
	}
	return hit;
}
        
bool tileGroup::mousePressed(int x, int y, int button) {
	bool hit = false;
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->mousePressed(x, y, button)) {
				hit = true;
				focus = it->getFeature();
			}
		}
	} else {
		if (focus->mousePressed(x, y, button)) hit = true;
	}
	return hit;
}
        
bool tileGroup::mouseReleased(int x, int y, int button) {
	bool hit = false;
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->mouseReleased(x, y, button)) hit = true;
		}
	} else {
		if (focus->mouseReleased(x, y, button)) hit = true;
	}
	return hit;
}

/*
 * Add a tile to the group.
 */
void tileGroup::addTile(tile t) {
	tiles.push_back(t);
}

/*
 * Return whether or not the tile group is, or is about to be, animating.
 */
bool tileGroup::isAnimating() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		if (it->isAnimating()) return true;
	}
	
	return false;
}

/*
 * Setup the tile group's entrance onto the wall.  Set each tile to come in 
 * from a random edge.
 */
void tileGroup::setupEntrance() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setupEntrance(randomScreenEdge());
	}
}

/*
 * Setup the tile group's exit from the wall.  Set each tile to exit the 
 * screen from random edge.
 */
void tileGroup::setupExit() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setupExit(randomScreenEdge());
	}
}

/*
 * Determine a random edge of the wall.  This is based on the relative 
 * position of the tile group - so the far left group can only deal with
 * the left, top, and bottom edges of the screen, etc.
 *
 * Default to the top of the screen.
 */
int tileGroup::randomScreenEdge() {
	int edge = EDGE_TOP;
	
	//Because of the way the enumeration was setup
	//we can just generate a random number between the
	//values.
	if (index == 0) {
		edge = (int)ofRandom(EDGE_LEFT, EDGE_BOTTOM+1);
	} else if (index == SCREENS-1) {
		edge = (int)ofRandom(EDGE_TOP, EDGE_RIGHT+1);
	} else {
		edge = (int)ofRandom(EDGE_TOP, EDGE_BOTTOM+1);
	}

	return edge;
}