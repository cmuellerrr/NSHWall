#pragma once

#include "ofMain.h"
#include "featureTile.h"
#include "pointAnimation.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile {

    public:

		tile(float column, float row, float columnSpan, float rowSpan, bool click = true);
		~tile();

		void update();
		void draw();

        bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		bool isAnimating();

		void setupEntrance();
		void setupExit();

		void setOffscreenPosition(ofPoint p) {offscreenPosition = p;}
		ofPoint getFinalPosition() {return finalPosition;}
		void setFinalPosition(ofPoint p) {finalPosition = p;}

		ofRectangle getGridRect() {return gridRect;}
		ofRectangle getTileRect() {return tileRect;}
		featureTile* getFeature() {return &feature;}

    protected:

		bool clickable;
		ofPoint offscreenPosition;
		ofPoint finalPosition;

		ofRectangle gridRect;
		ofRectangle tileRect;

		featureTile feature;

		list<animation*> animations;

	private: 
		int id;
		string title;
		string content;
		//media
};