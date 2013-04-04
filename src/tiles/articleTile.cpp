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
    
    textContent.init("Lato-Bla", 14);
    textContent.setText("Project Title");
    textContent.wrapTextX(this->tileRect.getWidth() - 2 * 10);
    textContent.setColor(255,255,255,255);
    
    tileColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    
    ofFbo::Settings fboSettings;
    fboSettings.internalformat = GL_RGBA32F_ARB;
    fboSettings.useDepth = true;
    fboSettings.useStencil = true;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    fboSettings.width = this->tileRect.getWidth();
    fboSettings.height = this->tileRect.getHeight();
    fboSettings.numSamples = 2;
    
    fbo.allocate(fboSettings);
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    fbo.begin();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(tileColor);
    ofRect(0,0,this->tileRect.getWidth(),this->tileRect.getHeight());
    textContent.setColor(0, 0, 0, 255);
    textContent.drawLeft(10, fbo.getHeight() - 10 - textContent.getHeight() + 1);
    textContent.setColor(255, 255, 255, 100);
    textContent.drawLeft(10, fbo.getHeight() - 10 - textContent.getHeight());
    ofDisableAlphaBlending();
    ofPopStyle();
    fbo.end();

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
//			ofFill();
//			ofRect(tileRect);
		}
        fbo.getTextureReference().bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        //        glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE,GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        fbo.draw(tileRect.getPosition().x, tileRect.getPosition().y, tileRect.getWidth(), tileRect.getHeight());
        glDisable(GL_BLEND);
        fbo.getTextureReference().unbind();
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