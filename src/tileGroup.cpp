#include "tileGroup.h"

tileGroup::tileGroup(ofRectangle bounds) {
	boundingBox = bounds;
	focus = 0;

	background = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

tileGroup::~tileGroup() {
	
}

void tileGroup::update() {
	if (focus == 0) {
		for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
			it->update();
		}
	} else {
		focus->update();
	}
}
		
void tileGroup::draw() {
	ofPushMatrix();
	ofTranslate(boundingBox.getPosition());

	ofPushStyle();
	ofSetColor(background);

	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->draw();
	}
	if (focus != 0) focus->draw();

	ofPopStyle();
	ofPopMatrix();
}

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
			if (it->mousePressed(x, y, button)) hit = true;
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

void tileGroup::addTile(tile t) {
	tiles.push_back(t);
}

bool tileGroup::isAnimating() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		if (it->isAnimating()) return true;
	}
	
	return false;
}

void tileGroup::setupEntrance() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setupEntrance();
	}
}

void tileGroup::setupExit() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setupExit();
	}
}