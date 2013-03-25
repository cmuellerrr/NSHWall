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
	
	clickable = click;
	
	gridRect = ofRectangle(column, row, columnSpan, rowSpan);

	int x = (wall::TILE_W * column) + MARGIN_TILE;
	int y = (wall::TILE_H * row) + MARGIN_TILE;
	int w = (wall::TILE_W * columnSpan) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * rowSpan) - (MARGIN_TILE * 2);

	finalPosition = ofPoint(x, y);
	tileRect = ofRectangle(finalPosition, w, h);

	position.setPosition(finalPosition);
}

tile::~tile() {
	
}

/*
 * Update the tile.  We really only care if it is animating.
 */
void tile::update() {
	if (position.isOrWillBeAnimating()) {
		position.update(1.0f / ofGetFrameRate());
		tileRect.setPosition(position.getCurrentPosition());
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
	return position.isOrWillBeAnimating();
}

/*
 * Set up the tile's entrance to the wall.
 */
void tile::setupEntrance(int edge) {
	//Move the tile off screen
	position.setPosition(getOffscreenPosition(edge));
	tileRect.setPosition(position.getCurrentPosition());

	//Animate to the desired position
	position.animateToAfterDelay(finalPosition, ofRandom(.5));
	position.setDuration(1.5);
	position.setRepeatType(PLAY_ONCE);
	position.setCurve(TANH);
}

/*
 * Set up the tile's exit from the wall.
 */
void tile::setupExit(int edge) {
	//Animate to its offscreen position
	position.animateToAfterDelay(getOffscreenPosition(edge), ofRandom(.5));
	position.setDuration(1.5);
	position.setRepeatType(PLAY_ONCE);
	position.setCurve(TANH);
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