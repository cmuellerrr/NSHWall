#include "routineManager.h"

routineManager::routineManager() {
	std::cout<<"Setting up routine manager"<<'\n';
	
	activeRoutine = 0;
	incomingRoutine = 0;

	resetHitTimer();
}

routineManager::~routineManager() {

}

void routineManager::update() {
	if (activeRoutine != 0) activeRoutine->update();
	
	if (incomingRoutine == 0 && ofGetElapsedTimeMillis() - lastHit >= IDLE_THRESHOLD) {
		std::cout<<"Moving to new routine due to idle time. "<<lastHit<<'\n';
		//transition to new routine
		cycleRoutine();
	}

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

void routineManager::draw() {
	if (activeRoutine != 0) activeRoutine->draw();
}

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

void routineManager::addRoutine(routine r){
	routines.push_back(r);

	if (routines.size() == 1) {
		activeRoutine = &routines.front();
		activeRoutine->setMode(ENTER);
		resetHitTimer();
	}
}

void routineManager::removeRoutine(routine* r){
	int index = getRoutineIndex(r);
    list<routine>::iterator it = routines.begin();
	if (index >= 0) {
		advance(it, index);
		routines.erase(it);
	}
}

void routineManager::cycleRoutine() {
	int nextRoutineIndex = getRoutineIndex(activeRoutine) + 1;
	if (nextRoutineIndex >= routines.size()) nextRoutineIndex = 0;
	setIncomingRoutine(getRoutineAt(nextRoutineIndex));
}

void routineManager::setIncomingRoutine(routine* r) {
	incomingRoutine = r;
	incomingRoutine->setMode(DONE);
	activeRoutine->setMode(EXIT);
	resetHitTimer();
}

int routineManager::getRoutineIndex(routine* r) {
	int index = 0;
	for (list<routine>::iterator it = routines.begin(); it != routines.end(); it++) {
		if (&*it == r) return index;
		index++;
	}
	return -1;
}

routine* routineManager::getRoutineAt(int index) {
    list<routine>::iterator it = routines.begin();
	advance(it, index);
	return &*it;
}

void routineManager::resetHitTimer() {
	lastHit = ofGetElapsedTimeMillis();
	std::cout<<"Resetting hit timer to "<<lastHit<<'\n';
}