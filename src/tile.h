#pragma once

#include "ofMain.h"
#include "featureTile.h"
#include "pointAnimation.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile {

    public:

		tile(int id, float column, float row, float columnSpan, float rowSpan, bool clickable = true);
		~tile();

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

		ofRectangle getGridRect() {return gridRect;}
		ofRectangle getTileRect() {return tileRect;}
		featureTile* getFeature() {return &feature;}

		int getState() {return state;}
		void setState(int newState);

    protected:
		int state;
		int id;
		bool clickable;

		ofPoint offscreenPosition;
		ofPoint finalPosition;

		ofRectangle gridRect;
		ofRectangle tileRect;

		featureTile feature;

		list<animation*> animations;

	private:

		string title;
		string content;
		//media
};