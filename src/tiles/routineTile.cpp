/*
 * A class representing tiles that are shown as part of a routine.
 * Have basic functionality to enter and exit the screen.
 */

#include "wall.h"
#include "routineTile.h"

/*
 * Create the tile with the given parameters.  Every constructor
 * calls the 'set' function with default parameters if not required by 
 * the constructor.
 */
routineTile::routineTile() {
	set(ofRandom(1000), ofRectangle(0, 0, 0, 0), true);
}

routineTile::routineTile(int id) {
	set(id, ofRectangle(0, 0, 0, 0), true);
}

routineTile::routineTile(int id, ofRectangle gridRect) {
	set(id, gridRect, true);
}
		
routineTile::routineTile(int id, ofRectangle gridRect, bool clickable) {
	set(id, gridRect, clickable);
}

routineTile::~routineTile() {
	//TODO clean up the animation objects.
}

/*
 * Do the actual work for setting up the tile.
 */
void routineTile::set(int id, ofRectangle gridRect, bool clickable) {
	state = HIDDEN;
	this->id = id;
	this->gridRect = gridRect;
	this->clickable = clickable;

	translateGridDimensions();
}

/*
 * Respond to mouse clicks.  The tile must be clickable.
 */
bool routineTile::mousePressed(int x, int y, int button) {
	return (clickable && tileRect.inside(x, y));
}

/*
 * Check for any state transitions based on the tile's
 * current state.  If found, update the tile's current state.
 */
void routineTile::checkStateTransition() {
	if (state == ENTER && animations.empty()) setState(ACTIVE);
	if (state == EXIT && animations.empty()) setState(HIDDEN);
}

/*
 * Set the tile's state.
 * The animation objects are getting allocated to the heap so make sure they get deleted when done.
 */
void routineTile::setState(int newState) {
	std::cout<<"Setting tile ("<<id<<") state to "<<newState<<'\n';
	
	state = newState;

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
}
