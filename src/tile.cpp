/*
 * A class representing tiles in their simplest form.  They hold the basic information
 * that is presented by the wall.  This class was written to be subclassed to tailor
 * tile behavior to the type of information being presented.
 */

#include "wall.h"
#include "tile.h"

/*
 * Create a tile with the given logical posion and size.  The actual position and
 * size are determined based off of the static variables created in the wall class.
 * You may also specity if tiles are clickable or not.
 */
tile::tile(float column, float row, float columnSpan, float rowSpan, bool click) {
	cout<<"Setting up tile \n";

	id = 0;
	title = "";
	content = "";

	clickable = click;
	
	gridRect = ofRectangle(column, row, columnSpan, rowSpan);

	int x = (wall::TILE_W * column) + MARGIN_TILE;
	int y = (wall::TILE_H * row) + MARGIN_TILE;
	int w = (wall::TILE_W * columnSpan) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * rowSpan) - (MARGIN_TILE * 2);

	finalPosition = ofPoint(x, y);
	tileRect = ofRectangle(finalPosition, w, h);
}

tile::~tile() {
	
}

/*
 * Update the tile.  We really only care if it is animating.
 * Update any animations it has, and remove any that are done.
 */
void tile::update() {
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
}

/*
 * Draw the tile.
 */
void tile::draw() {
	ofPushStyle();

	ofFill();
	ofRect(tileRect);

	ofPopStyle();
}

/*
 * Handle all input.  Return if something happened.
 */

bool tile::mouseMoved(int x, int y)  {
	return false;
}

bool tile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool tile::mousePressed(int x, int y, int button) {
	if (clickable && tileRect.inside(x, y)) {
		cout<<"HIT at "<<x<<" "<<y<<"\n";
		feature.setMode(ENTER);
		return true;
	}
	return false;
}
        
bool tile::mouseReleased(int x, int y, int button) {
	return false;
}

/*
 * Return if the tile is, or will be, animating.
 */
bool tile::isAnimating() {
	return !animations.empty();
}

/*
 * Set up the tile's entrance to the wall.
 */
void tile::setupEntrance(int edge) {
	//Move the tile off screen
	tileRect.setPosition(getOffscreenPosition(edge));

	//This is getting allocated to the heap so make sure it gets deleted when done.
	animations.push_front(new pointAnimation(&tileRect.position, finalPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
}

/*
 * Set up the tile's exit from the wall.
 */
void tile::setupExit(int edge) {
	//This is getting allocated to the heap so make sure it gets deleted when done.
	animations.push_front(new pointAnimation(&tileRect.position, getOffscreenPosition(edge), 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
}

/*
 * Get a point representing some offscreen position for the given edge.
 * So, if edge is the left edge, it will return a point guaranteed to 
 * be offscreen and to the left of the wall.
 */
ofPoint tile::getOffscreenPosition(int edge) {
	ofPoint p = ofPoint(finalPosition);

	switch (edge) {
		case EDGE_LEFT:
				p.x = -ofGetWindowWidth() * SCREENS;
			break;
		case EDGE_TOP:
				p.y = -ofGetWindowHeight();
			break;
		case EDGE_RIGHT:
				p.x = ofGetWindowWidth() * SCREENS;
			break;
		case EDGE_BOTTOM:
				p.y = ofGetWindowHeight() * 2;
			break;
		default:
			break;
	}

	return p;
}