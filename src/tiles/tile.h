#pragma once

#include "ofMain.h"
#include "animation.h"
#include "ofxTextSuite.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile {

    public:

		virtual ~tile();

		virtual void update();
		virtual void draw();

        virtual bool mouseMoved(int x, int y);
        virtual bool mouseDragged(int x, int y, int button);
        virtual bool mousePressed(int x, int y, int button);
        virtual bool mouseReleased(int x, int y, int button);

		virtual void checkStateTransition() = 0;

		virtual bool isAnimating();		

		virtual int getState() {return state;}
		virtual void setState(int newState) = 0;
		virtual int getId() {return id;}

		virtual ofPoint getDefaultPosition() {return defaultPosition;}
		virtual void setDefaultPosition(ofPoint p) {defaultPosition = p;}
		virtual ofPoint getOffscreenPosition() {return offscreenPosition;}
		virtual void setOffscreenPosition(ofPoint p) {offscreenPosition = p;}

		virtual ofRectangle getGridRect() {return gridRect;}
		virtual ofRectangle getTileRect() {return tileRect;}

		virtual tile* getWhenFocused() {return 0;}

    protected:

		virtual void translateGridDimensions();

		int state;
		int id;

		ofPoint defaultPosition;
		ofPoint offscreenPosition;

		ofRectangle gridRect;
		ofRectangle tileRect;

		list<animation*> animations;

};