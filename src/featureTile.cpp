#include "wall.h"
#include "featureTile.h"

/*
 *
 */
featureTile::featureTile() {
	mode = HIDDEN;

	int x = (wall::TILE_W / 2) + MARGIN_TILE;
	int y = (wall::TILE_H * 0.75) + MARGIN_TILE;
	int w = (wall::SCREEN_W * 0.75) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * (ROWS - 2));

	finalSize = ofPoint(w, h);
	tileRect = ofRectangle(x, y, 0, 0);
}

featureTile::~featureTile() {
	
}


/*
 * Update the tile.  We really only care if it is animating.
 * Update any animations it has, and remove any that are done.
 */
void featureTile::update() {
	//This is a little different because we are removing things while traversing
	for (list<animation*>::iterator it = animations.begin(); it != animations.end();) {
		if ((*it)->isDone()) {
			delete *it;
			it = animations.erase(it);
		}
		else {
			(*it)->update();
			++it;
		}
	}
	if (mode == EXIT && animations.empty()) mode = HIDDEN;\
}

/*
 * Draw the tile.
 */
void featureTile::draw() {
	ofPushStyle();
	
	ofSetColor(ofColor(128, 128, 128));
	ofFill();
	ofRect(tileRect);

	ofPopStyle();
}

/*
 * Handle all input.  Return if something happened.
 */

bool featureTile::mouseMoved(int x, int y)  {
	return false;
}

bool featureTile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool featureTile::mousePressed(int x, int y, int button) {
	if (tileRect.inside(x, y)) {
		cout<<"HIT at "<<x<<" "<<y<<"\n";
		setMode(EXIT);
	}
	return false;
}
        
bool featureTile::mouseReleased(int x, int y, int button) {
	return false;
}

/*
 * Return if the tile is, or will be, animating.
 */
bool featureTile::isAnimating() {
	return !animations.empty();\
}


/*
 * Set up the tile's entrance to the wall.
 */
void featureTile::setupEntrance() {
	//This is getting allocated to the heap so make sure it gets deleted when done.
	animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, finalSize, .3, BOUNCY));
}

/*
 * Set up the tile's exit from the wall.
 */
void featureTile::setupExit() {
	//This is getting allocated to the heap so make sure it gets deleted when done.
	animations.push_front(new dimensionAnimation(&tileRect.width, &tileRect.height, ofPoint(0, 0), .3, BOUNCY));
}

void featureTile::setMode(int newMode) {
	std::cout<<"Setting feature mode to "<<newMode<<'\n';
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