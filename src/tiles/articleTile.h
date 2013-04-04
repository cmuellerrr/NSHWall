#pragma once

#include "ofMain.h"
#include "routineTile.h"
#include "expandedTile.h"
#include "pointAnimation.h"


class articleTile : public routineTile {

    public:

		articleTile();
		articleTile(int id, string title);
		articleTile(int id, string title, string content);
		articleTile(int id, string title, ofRectangle gridRect);
		articleTile(int id, string title, ofRectangle gridRect, bool clickable);
		articleTile(int id, string title, string content, ofRectangle gridRect);
		articleTile(int id, string title, string content, ofRectangle gridRect, bool clickable);
		~articleTile();

		void draw();

        bool mousePressed(int x, int y, int button);
		
		tile* getWhenFocused() {return &expanded;}

		void setContent(string content);

		void setFeaturedImage(string url);
		void setFeaturedImage(ofImage img);

		void addImage(string url);
		void addImage(ofImage img);

    protected:
		
		string title;
		ofImage featuredImg;			
		
		expandedTile expanded;
    
        ofxTextBlock textContent;
        ofFbo fbo;
        ofColor tileColor;

	private:

		void set(int id, string title, string content, ofRectangle gridRect, bool clickable);
};