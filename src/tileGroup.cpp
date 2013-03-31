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
tileGroup::tileGroup() {
	set(0, ofRectangle(0, 0, 0, 0));
}

tileGroup::tileGroup(int index, ofRectangle boundingBox) {
	set(index, boundingBox);
}

/*
 * Do the actual work for setting up the group.
 */
void tileGroup::set(int index, ofRectangle boundingBox) {
	this->index = index;
	this->boundingBox = boundingBox;

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
	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->update();
	}

	if (focus != 0) {
		focus->update();
		if (focus->getState() == HIDDEN) {
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

	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
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
		for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
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
		for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
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
		for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			if (it->mousePressed(x, y, button)) {
				hit = true;
				focus = it->getExpanded();
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
		for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
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
void tileGroup::addTile(gridTile t) {
	t.setOffscreenPosition(getClosestOffscreenPosition(t));
	tiles.push_back(t);
}

/*
 * Remove the given tile from the group.
 */
void tileGroup::removeTile(gridTile* t) {
	int index = getTileIndex(t);
    list<gridTile>::iterator it = tiles.begin();
	if (index >= 0) {
		advance(it, index);
		tiles.erase(it);
	}
}

/*
 * Get the index of the given tile.
 */
int tileGroup::getTileIndex(gridTile* t) {
	int index = 0;
	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		if (&*it == t) return index;
		index++;
	}
	return -1;
}

/*
 * Get a pointer to the tile at the specified index.
 */
gridTile* tileGroup::getTileAt(int index) {
    list<gridTile>::iterator it = tiles.begin();
	advance(it, index);
	return &*it;
}

/*
 * Return whether or not the tile group is, or is about to be, animating.
 */
bool tileGroup::isAnimating() {
	if (focus != 0) return true;

	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		if (it->isAnimating()) return true;
	}
	
	return false;
}

/*
 * Setup the tile group's entrance onto the wall.  Set each tile to come in 
 * from a random edge.
 */
void tileGroup::setupEntrance() {
	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setState(ENTER);
	}
}

/*
 * Setup the tile group's exit from the wall.  Set each tile to exit the 
 * screen from random edge.  If there is a focused tile, make sure that 
 * gets set to disappear.
 */
void tileGroup::setupExit() {
	if (focus != 0) focus->setState(EXIT);

	for (list<gridTile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setState(EXIT);
	}
}

/*
 * Determine the closest edge of the wall.  This is based on the relative 
 * position of the tile group - so the far left group can only deal with
 * the left, top, and bottom edges of the screen, etc.
 *
 * Default to the top of the screen.
 */
ofPoint tileGroup::getClosestOffscreenPosition(gridTile t) {
	int edge = EDGE_TOP;
	
	ofRectangle grid = t.getGridRect();
	int col = grid.getX();
	int row = grid.getY();

	//Leftmost screen
	if (index == 0) {
		if (col == 0 || col == 1 && (row == 2 || row == 3)) {
			edge = EDGE_LEFT;
		} else if (row < ROWS/2) {
			edge = EDGE_TOP;
		} else {
			edge = EDGE_BOTTOM;
		}
	//Rightmost screen
	} else if (index == SCREENS-1) {
		if (col == COLUMNS-1 || col == COLUMNS-2 && (row == 2 || row == 3)) {
			edge = EDGE_RIGHT;
		} else if (row < ROWS/2) {
			edge = EDGE_TOP;
		} else {
			edge = EDGE_BOTTOM;
		}
	//Middle screens
	} else {
		if (row < ROWS/2) {
			edge = EDGE_TOP;
		} else {
			edge = EDGE_BOTTOM;
		}
	}

	ofPoint p = ofPoint(t.getFinalPosition());

	switch (edge) {
		case EDGE_LEFT:
				p.x = -ofGetWindowWidth() * SCREENS;
			break;
		case EDGE_TOP:
				p.y = -ofGetWindowHeight();
			break;
		case EDGE_RIGHT:
				p.x = ofGetWindowWidth() * SCREENS;
			break;
		case EDGE_BOTTOM:
				p.y = ofGetWindowHeight() * 2;
			break;
		default:
			break;
	}

	return p;
}