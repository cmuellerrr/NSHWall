#include "wall.h"
#include "tileGroup.h"

tileGroup::tileGroup(ofRectangle bounds) {
	boundingBox = bounds;
	focus = 0;

	//Determine the group's position relative to the entire
	//wall.  Meaning, is it the far left, far right, or one 
	//of the middle screens.
	if (bounds.x <= wall::SCREEN_W) {
		relativePosition = FARLEFT;
	//I don't wan to make the fenster canvas accessible from here,
	//so just compute the distance.
	} else if (bounds.x >= wall::SCREEN_W * (SCREENS - 1)) {
		relativePosition = FARRIGHT;
	} else {
		relativePosition = MIDDLE;
	}

	tileColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
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
	ofSetColor(tileColor);

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
		it->setupEntrance(randomScreenEdge());
	}
}

void tileGroup::setupExit() {
	for (list<tile>::iterator it = tiles.begin(); it != tiles.end(); it++) {
		it->setupExit(randomScreenEdge());
	}
}

int tileGroup::randomScreenEdge() {
	int edge = EDGE_TOP;
	
	//Because of the way the enumeration was setup
	//we can just generate a random number between the
	//values.
	if (relativePosition == FARLEFT) {
		edge = (int)ofRandom(EDGE_LEFT, EDGE_BOTTOM+1);
	} else if (relativePosition == FARRIGHT) {
		edge = (int)ofRandom(EDGE_TOP, EDGE_RIGHT+1);
	} else {
		edge = (int)ofRandom(EDGE_TOP, EDGE_BOTTOM+1);
	}

	return edge;
}