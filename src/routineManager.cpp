/*
 * A class that handles the overall logic of routines.  Determines
 * the active routine, passing all input,  and deals with the switching 
  *between different ones.  
 */

#include "routineManager.h"

/*
 * Default constructor.
 */
routineManager::routineManager() {
	std::cout<<"Setting up routine manager"<<'\n';
	
	activeRoutine = 0;
	incomingRoutine = 0;

	resetHitTimer();
}

routineManager::~routineManager() {

}

/*
 * Update the current routine.  If there hasn't been any interactions for a
 * while then begin the transition to a new routine.  Handles the actual
 * switchover when the outgoing routine is done exiting.
 */
void routineManager::update() {
	if (activeRoutine != 0) activeRoutine->update();
	
	//If nobody has interacted with it in a while
	if (incomingRoutine == 0 && ofGetElapsedTimeMillis() - lastHit >= IDLE_THRESHOLD) {
		std::cout<<"Moving to new routine due to idle time. "<<lastHit<<'\n';
		//transition to new routine
		cycleRoutine();
	}

	//Switch to the incoming routine if the outgoing one has finished
	if (incomingRoutine != 0) {
		if (activeRoutine->getMode() == DONE) {
			std::cout<<"Swaping active routine"<<'\n';
			std::cout<<"Active Routine - "<<activeRoutine->getMode()<<'\n';
			std::cout<<"Incoming Routine - "<<incomingRoutine->getMode()<<'\n';
			activeRoutine = incomingRoutine;
			activeRoutine->setMode(ENTER);
			incomingRoutine = 0;
		}
	}
}

/*
 * Draw the active routine.
 */
void routineManager::draw() {
	if (activeRoutine != 0) activeRoutine->draw();
}


/*
 * Handle all input.  Just pass it to the active routine and
 * take note when anything actually happens.
 */


void routineManager::keyPressed(int key){
	if (key == OF_KEY_RIGHT) cycleRoutine();
}


void routineManager::mouseMoved(int x, int y ) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mouseMoved(x, y);
	}
}

void routineManager::mouseDragged(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mouseDragged(x, y, button);
		if (hit) resetHitTimer();
	}
}

void routineManager::mousePressed(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mousePressed(x, y, button);
		if (hit) resetHitTimer();
	}
}

void routineManager::mouseReleased(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mouseReleased(x, y, button);
		if (hit) resetHitTimer();
	}
}

/*
 * Add the given routine to the list of available routines.
 * If this is the only one, then set it as avtive.
 */
void routineManager::addRoutine(routine r){
	routines.push_back(r);

	if (routines.size() == 1) {
		activeRoutine = &routines.front();
		activeRoutine->setMode(ENTER);
		resetHitTimer();
	}
}

/*
 * Remove the given routine from the list of available
 * routines.  Some ugliness due to the way lists need
 * to be modified.
 */
void routineManager::removeRoutine(routine* r){
	int index = getRoutineIndex(r);
    list<routine>::iterator it = routines.begin();
	if (index >= 0) {
		advance(it, index);
		routines.erase(it);
	}
}

/*
 * Cycle the avtive routine to the next in the list.
 * If you are at the end then cycle back to the beginnig.
 */
void routineManager::cycleRoutine() {
	int nextRoutineIndex = getRoutineIndex(activeRoutine) + 1;
	if (nextRoutineIndex >= routines.size()) nextRoutineIndex = 0;
	setIncomingRoutine(getRoutineAt(nextRoutineIndex));
}

/*
 * Set the given routine as the next one up.  This tells
 * the currently active routine to exit.  
 */
void routineManager::setIncomingRoutine(routine* r) {
	incomingRoutine = r;
	//Probably not necessary to set this to DONE
	incomingRoutine->setMode(DONE);
	activeRoutine->setMode(EXIT);
	resetHitTimer();
}

/*
 * Get the index of the given routine.
 */
int routineManager::getRoutineIndex(routine* r) {
	int index = 0;
	for (list<routine>::iterator it = routines.begin(); it != routines.end(); it++) {
		if (&*it == r) return index;
		index++;
	}
	return -1;
}

/*
 * Get a pointer to the routine at the specified index.
 */
routine* routineManager::getRoutineAt(int index) {
    list<routine>::iterator it = routines.begin();
	advance(it, index);
	return &*it;
}

/*
 * Reset the idle timer - the last time the wall was 
 * interacted with.
 */
void routineManager::resetHitTimer() {
	lastHit = ofGetElapsedTimeMillis();
	std::cout<<"Resetting hit timer to "<<lastHit<<'\n';
}