#include "routineManager.h"

routineManager::routineManager() {
	std::cout<<"Setting up routine manager"<<'\n';
	
	activeRoutine = 0;
	nextRoutine = 0;

	lastHit = ofGetMinutes();
}

routineManager::~routineManager() {

}

void routineManager::update() {
	if (activeRoutine != 0) activeRoutine->update();
	
	if (nextRoutine == 0 && ofGetMinutes() - lastHit >= IDLE_THRESHOLD) {
		std::cout<<"Moving to new routine due to idle time."<<'\n';
		//transition to new routine
		cycleRoutine();
	}

	if (nextRoutine != 0) {
		if (activeRoutine->getMode() == DONE) {
			activeRoutine = nextRoutine;
			activeRoutine->setMode(ENTER);
			nextRoutine = 0;
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
		if (hit) lastHit = ofGetMinutes();
	}
}

void routineManager::mouseDragged(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mouseDragged(x, y, button);
		if (hit) lastHit = ofGetMinutes();
	}
}

void routineManager::mousePressed(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mousePressed(x, y, button);
		if (hit) lastHit = ofGetMinutes();
	}
}

void routineManager::mouseReleased(int x, int y, int button) {
	if (activeRoutine != 0) {
		bool hit = activeRoutine->mouseReleased(x, y, button);
		if (hit) lastHit = ofGetMinutes();
	}
}

void routineManager::addRoutine(routine r){
	routines.push_back(r);

	if (routines.size() == 1) {
		activeRoutine = &routines.front();
		activeRoutine->setMode(ENTER);
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
	setNextRoutine(getRoutineAt(nextRoutineIndex));
	lastHit = ofGetMinutes();
}

void routineManager::setNextRoutine(routine* r) {
	nextRoutine = r;
	activeRoutine->setMode(EXIT);
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