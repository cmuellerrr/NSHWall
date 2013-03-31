/*
 * A class representing tiles in their simplest form.  They hold the basic information
 * that is presented by the wall.  This class was written to be subclassed to tailor
 * tile behavior to the type of information being presented.
 */

#include "wall.h"
#include "gridTile.h"

/*
 * Create a tile with the given logical posion and size.  The actual position and
 * size are determined based off of the static variables created in the wall class.
 * You may also specity if tiles are clickable or not.
 */
gridTile::gridTile() {
	set(ofRandom(1000), "", "", ofRectangle(0, 0, 0, 0), true);
}

gridTile::gridTile(int id, string title) {
	set(id, title, "", ofRectangle(0, 0, 0, 0), true);
}
		
gridTile::gridTile(int id, string title, string content) {
	set(id, title, content, ofRectangle(0, 0, 0, 0), true);
}
		
gridTile::gridTile(int id, string title, ofRectangle gridRect) {
	set(id, title, "", gridRect, true);
}
	
gridTile::gridTile(int id, string title, ofRectangle gridRect, bool clickable) {
	set(id, title, "", gridRect, clickable);
}

gridTile::gridTile(int id, string title, string content, ofRectangle gridRect) {
	set(id, title, content, gridRect, true);
}
		
gridTile::gridTile(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	set(id, title, content, gridRect, clickable);
}

gridTile::~gridTile() {
	
}

/*
 * Do the actual work for setting up the tile.
 */
void gridTile::set(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	state = HIDDEN;
	this->id = id;
	this->title = title;
	this->gridRect = gridRect;
	this->clickable = clickable;

	int x = (wall::TILE_W * gridRect.x) + MARGIN_TILE;
	int y = (wall::TILE_H * gridRect.y) + MARGIN_TILE;
	int w = (wall::TILE_W * gridRect.width) - (MARGIN_TILE * 2);
	int h = (wall::TILE_H * gridRect.height) - (MARGIN_TILE * 2);

	offscreenPosition = ofPoint(x, -ofGetWindowHeight());
	finalPosition = ofPoint(x, y);
	tileRect = ofRectangle(finalPosition, w, h);

	expanded = expandedTile(id, title, content);
}

/*
 * Update the tile.  We really only care if it is animating.
 * Update any animations it has, and remove any that are done.
 */
void gridTile::update() {
	if (state != HIDDEN) {
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
		if (state == ENTER && animations.empty()) setState(ACTIVE);
		if (state == EXIT && animations.empty()) setState(HIDDEN);
	}
}

/*
 * Draw the tile.
 */
void gridTile::draw() {
	if (state != HIDDEN) {
		ofPushStyle();

		if (featuredImg.isAllocated()) {
			featuredImg.draw(tileRect);
		} else {
			ofFill();
			ofRect(tileRect);
		}

		ofPopStyle();
	}
}

/*
 * Handle all input.  Return if something happened.
 */

bool gridTile::mouseMoved(int x, int y)  {
	return false;
}

bool gridTile::mouseDragged(int x, int y, int button) {
	return false;
}
        
bool gridTile::mousePressed(int x, int y, int button) {
	if (clickable && tileRect.inside(x, y)) {
		cout<<"HIT at "<<x<<" "<<y<<"\n";
		expanded.setState(ENTER);
		return true;
	}
	return false;
}
        
bool gridTile::mouseReleased(int x, int y, int button) {
	return false;
}

/*
 * Return if the tile is, or will be, animating.
 */
bool gridTile::isAnimating() {
	return !animations.empty();
}

/*
 * Set the tile's state.
 * The animation objects are getting allocated to the heap so make sure they get deleted when done.
 */
void gridTile::setState(int newState) {
	std::cout<<"Setting tile ("<<id<<") state to "<<newState<<'\n';
	switch (newState) {
		case ENTER:
			//Move the tile off screen
			tileRect.setPosition(offscreenPosition);
			animations.push_front(new pointAnimation(&tileRect.position, finalPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
		case EXIT:
			animations.push_front(new pointAnimation(&tileRect.position, offscreenPosition, 1.5, TANH, PLAY_ONCE, ofRandom(.5)));
			break;
	}	
	state = newState;
}

void gridTile::setContent(string content) {
	expanded.setContent(content);
}

void gridTile::setFeaturedImage(string url) {
	ofImage img;

	if (img.loadImage(url)) {
		setFeaturedImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

void gridTile::setFeaturedImage(ofImage img) {
	featuredImg = img;
	addImage(img);
}

void gridTile::addImage(string url) {
	ofImage img;
	if (img.loadImage(url)) {
		expanded.addImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

void gridTile::addImage(ofImage img) {
	expanded.addImage(img);
}