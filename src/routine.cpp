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
routine::routine() {
	std::cout<<"Setting up routine."<<'\n';
	mode = HIDDEN;
}

routine::~routine() {

}

/*
 * Update the routine when making its entrance.
 * Handle the state change when the entrance is complete.
 */
void routine::updateEnter() {
	updateActive();

	bool allDone = true;

	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->isAnimating()) allDone = false;
	}

	if (allDone) setMode(ACTIVE);
}

/*
 * Update the routine when in its normal, active state.
 */
void routine::updateActive() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->update();
	}
}

/*
 * Update the routine when it is exiting the wall.
 * Handle the state change when done.
 */
void routine::updateExit() {
	updateActive();

	bool allDone = true;

	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->isAnimating()) allDone = false;
	}

	if (allDone) setMode(HIDDEN);
}

/*
 * Draw the routine when entering the all.
 */
void routine::drawEnter() {
	drawActive();
}
		
/*
 * Draw the wall in its normal state.
 */
void routine::drawActive() {

	ofPushStyle();

    ofSetColor(255, 255, 255);
    ofFill();
	
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->draw();
	}

	ofPopStyle();
}

/*
 * Draw the wall when exiting.
 */		
void routine::drawExit() {
	drawActive();
}


/*
 * Handle all input.  Just pass to the tile groups.
 */

//TODO: we can find a better way of comparing the group index.
//Maybe their index within the group list should match?  But what
//if we go to a 2D set of displays?

bool routine::mouseMoved(int x, int y, int screen)  {
	bool hit = false;
	if (mode == ACTIVE) {
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
	if (mode == ACTIVE) {
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
	if (mode == ACTIVE) {
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
	if (mode == ACTIVE) {
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
void routine::setMode(int newMode) {
	std::cout<<"Setting routine mode to "<<newMode<<'\n';
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

/*
 * Add a tile group to the routine.
 */
void routine::addGroup(tileGroup g) {
	groups.push_back(g);
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