#pragma once

#include "ofMain.h"
#include "expandedTile.h"
#include "pointAnimation.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile {

    public:

		tile();
		tile(int id, string title);
		tile(int id, string title, string content);
		tile(int id, string title, ofRectangle gridRect);
		tile(int id, string title, ofRectangle gridRect, bool clickable);
		tile(int id, string title, string content, ofRectangle gridRect);
		tile(int id, string title, string content, ofRectangle gridRect, bool clickable);
		~tile();

		void set(int id, string title, string content, ofRectangle gridRect, bool clickable);

		void update();
		void draw();

        bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		bool isAnimating();		

		void setOffscreenPosition(ofPoint p) {offscreenPosition = p;}
		ofPoint getFinalPosition() {return finalPosition;}
		void setFinalPosition(ofPoint p) {finalPosition = p;}

		int getState() {return state;}
		void setState(int newState);

		ofRectangle getGridRect() {return gridRect;}
		ofRectangle getTileRect() {return tileRect;}
		expandedTile* getExpanded() {return &expanded;}

		void setContent(string content);
		void setFeaturedImage(string url);
		void setFeaturedImage(ofImage img);
		void addImage(string url);
		void addImage(ofImage img);

    protected:

		int state;
		int id;
		bool clickable;

		ofPoint offscreenPosition;
		ofPoint finalPosition;

		ofRectangle gridRect;
		ofRectangle tileRect;

		list<animation*> animations;

	private:

		string title;
		ofImage featuredImg;
		
		expandedTile expanded;
};