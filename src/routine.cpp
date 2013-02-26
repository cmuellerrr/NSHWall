#include "routine.h"

routine::routine() {
	std::cout<<"Setting up routine."<<'\n';
}

routine::~routine() {

}

void routine::setup() {
}

void routine::updateEnter() {
	updateActive();

	bool allDone = true;

	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->isAnimating()) allDone = false;
	}

	if (allDone) setMode(ACTIVE);
}
		
void routine::updateActive() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->update();
	}
}

void routine::updateExit() {
	updateActive();

	bool allDone = true;

	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		if (it->isAnimating()) allDone = false;
	}

	if (allDone) setMode(DONE);
}
		
void routine::drawEnter() {
	drawActive();
}
		
void routine::drawActive() {

	ofPushStyle();

    ofSetColor(255, 255, 255);
    ofFill();
	
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->draw();
	}

	ofPopStyle();
}
		
void routine::drawExit() {
	drawActive();
}

bool routine::mouseMoved(int x, int y)  {
	bool hit = false;
	if (mode == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if (it->mouseMoved(x, y)) hit = true;
		}
	}
	return hit;
}

bool routine::mouseDragged(int x, int y, int button) {
	bool hit = false;
	if (mode == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if (it->mouseDragged(x, y, button)) hit = true;
		}
	}
	return hit;
}
        
bool routine::mousePressed(int x, int y, int button) {
	bool hit = false;
	if (mode == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if (it->mousePressed(x, y, button)) hit = true;
		}
	}
	return hit;
}
        
bool routine::mouseReleased(int x, int y, int button) {
	bool hit = false;
	if (mode == ACTIVE) {
		for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
			if (it->mouseReleased(x, y, button)) hit = true;
		}
	}
	return hit;
}

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

void routine::addGroup(tileGroup g) {
	groups.push_back(g);
}

void routine::setupEntrance() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->setupEntrance();
	}
}

void routine::setupExit() {
	for (list<tileGroup>::iterator it = groups.begin(); it != groups.end(); it++) {
		it->setupExit();
	}
}