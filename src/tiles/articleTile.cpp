/*
 * A class representing article tiles shown on the grid.  They hold the basic information
 * that is presented by the wall such as title and featured image.  They 
 * also have an expanded version of themselves for when they are clicked on.
 */

#include "wall.h"
#include "articleTile.h"

/*
 * Create the tile with the given parameters.  Every constructor
 * calls the 'set' function with default parameters if not required by 
 * the constructor.
 */
articleTile::articleTile() {
	set(ofRandom(1000), "", "", ofRectangle(0, 0, 0, 0), true);
}

articleTile::articleTile(int id, string title) {
	set(id, title, "", ofRectangle(0, 0, 0, 0), true);
}
		
articleTile::articleTile(int id, string title, string content) {
	set(id, title, content, ofRectangle(0, 0, 0, 0), true);
}
		
articleTile::articleTile(int id, string title, ofRectangle gridRect) {
	set(id, title, "", gridRect, true);
}
	
articleTile::articleTile(int id, string title, ofRectangle gridRect, bool clickable) {
	set(id, title, "", gridRect, clickable);
}

articleTile::articleTile(int id, string title, string content, ofRectangle gridRect) {
	set(id, title, content, gridRect, true);
}
		
articleTile::articleTile(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	set(id, title, content, gridRect, clickable);
}

articleTile::~articleTile() {
	//TODO make sure to clean up images and the expanded tile
}

/*
 * Do the actual work for setting up the tile.
 */
void articleTile::set(int id, string title, string content, ofRectangle gridRect, bool clickable) {
	state = HIDDEN;
	this->id = id;
	this->title = title;
	this->gridRect = gridRect;
	this->clickable = clickable;

	translateGridDimensions();
	
	expanded = expandedTile(id, title, content);
}

/*
 * Draw the tile.
 */
void articleTile::draw() {
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

bool articleTile::mousePressed(int x, int y, int button) {
	if (clickable && tileRect.inside(x, y)) {
		expanded.setState(ENTER);
		return true;
	}
	return false;
}

/*
 * Set the tile's expandedTile content.
 */
void articleTile::setContent(string content) {
	expanded.setContent(content);
}

/*
 * Set the tile's featured image.  This image
 * then gets pushed to the expanded tile.
 */
void articleTile::setFeaturedImage(string url) {
	ofImage img;

	if (img.loadImage(url)) {
		setFeaturedImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

/*
 * Set the tile's featured image.  This image
 * then gets pushed to the expanded tile.
 */
void articleTile::setFeaturedImage(ofImage img) {
	featuredImg = img;
	addImage(img);
}

/*
 * Add the given image to the expanded tile.
 */
void articleTile::addImage(string url) {
	ofImage img;
	if (img.loadImage(url)) {
		expanded.addImage(img);
	} else {
		cout<<"FAILED TO LOAD IMAGE: "<<url<<"\n";
	}
}

/*
 * Add the given image to the expanded tile.
 */
void articleTile::addImage(ofImage img) {
	expanded.addImage(img);
}