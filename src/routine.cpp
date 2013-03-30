/*
 * A class representing the concept of a routine.  A routine is just a 
 * container for tile groups (or screens) but also handles the process
 * for how routines enter and exit the wall.  
 *
 * This class was set up to be subclassed so we can have the generic routines
 * which show tiles and also some other types of routines which can be 
 * more visually stimulating - like a crazy visualization when the screen has
 * been idle for a while.
 */

#include "routine.h"

/*
 * Default constructor.
 */
routine::routine(int i) {
	std::cout<<"Setting up routine ("<<i<<")."<<'\n';
	
	state = HIDDEN;
	
	id = i;
	name = "";
	start = 0;
	end = 0;
}

routine::~routine() {

}

/*
 * Update the routine.  Take care of any state transitions also.
 */
void routine::update() {
	if (state != HIDDEN) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			it->update();
		}
		
		bool animating = isAnimating();
		if (state == ENTER && !animating) setState(ACTIVE);
		else if (state == EXIT && !animating) setState(HIDDEN);
	}
}

/*
 * Draw the routine.
 */
void routine::draw() {
	ofPushStyle();

    ofSetColor(255, 255, 255);
    ofFill();
	
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->draw();
	}

	ofPopStyle();
}


/*
 * Handle all input.  Just pass to the tile groups.
 */


//TODO: we can find a better way of comparing the group index.
//Maybe their index within the group list should match?  But what
//if we go to a 2D set of displays?
bool routine::mouseMoved(int x, int y, int screen)  {
	bool hit = false;
	if (state == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if(it->getIndex() == screen) {
				if (it->mouseMoved(x, y)) hit = true;
			}
		}
	}
	return hit;
}

bool routine::mouseDragged(int x, int y, int button, int screen) {
	bool hit = false;
	if (state == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if(it->getIndex() == screen) {
				if (it->mouseDragged(x, y, button)) hit = true;
			}
		}
	}
	return hit;
}
        
bool routine::mousePressed(int x, int y, int button, int screen) {
	bool hit = false;
	if (state == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if(it->getIndex() == screen) {
				if (it->mousePressed(x, y, button)) hit = true;
			}
		}
	}
	return hit;
}
        
bool routine::mouseReleased(int x, int y, int button, int screen) {
	bool hit = false;
	if (state == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if(it->getIndex() == screen) {
				if (it->mouseReleased(x, y, button)) hit = true;
			}
		}
	}
	return hit;
}

/*
 * Set the wall's current mode.  Take care of setting up the 
 * tile groups in accordance with the new mode.
 */
void routine::setState(int newMode) {
	std::cout<<"Setting routine ("<<id<<") mode to "<<newMode<<'\n';
	switch (newMode) {
		case ENTER:
			setupEntrance();
			break;
		case EXIT:
			setupExit();
			break;
	}	
	state = newMode;
}

/*
 * Add a tile group to the routine.
 */
void routine::addGroup(tileGroup g) {
	groups.push_back(g);
}

void routine::removeGroup(tileGroup* g) {
	int index = getGroupIndex(g);
    list<tileGroup>::iterator it = groups.begin();
	if (index >= 0) {
		advance(it, index);
		groups.erase(it);
	}
}

/*
 * Get the index of the given tile group.
 */
int routine::getGroupIndex(tileGroup* g) {
	int index = 0;
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (&*it == g) return index;
		index++;
	}
	return -1;
}

/*
 * Get a pointer to the tileGroup at the specified index.
 */
tileGroup* routine::getGroupAt(int index) {
    list<tileGroup>::iterator it = groups.begin();
	advance(it, index);
	return &*it;
}

/*
 * Return weather or not the routine's groups are animating.
 */
bool routine::isAnimating() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->isAnimating()) return true;
	}
	return false;
}

/*
 * Setup the routine to begin its entrance to the wall.
 */
void routine::setupEntrance() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->setupEntrance();
	}
}

/*
 * Setup the routine to begin its exit from the wall.
 */
void routine::setupExit() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->setupExit();
	}
}