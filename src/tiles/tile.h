#pragma once

#include "ofMain.h"
#include "animation.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile {

    public:

		tile();
		tile(int id);
		tile(int id, ofRectangle gridRect);
		tile(int id, ofRectangle gridRect, bool clickable);
		~tile();

		virtual void update();
		virtual void draw();

        virtual bool mouseMoved(int x, int y);
        virtual bool mouseDragged(int x, int y, int button);
        virtual bool mousePressed(int x, int y, int button);
        virtual bool mouseReleased(int x, int y, int button);

		virtual void checkStateTransition();

		virtual bool isAnimating();		

		virtual int getState() {return state;}
		virtual void setState(int newState) {state = newState;}
		virtual int getId() {return id;}

		virtual ofPoint getDefaultPosition() {return defaultPosition;}
		virtual void setDefaultPosition(ofPoint p) {defaultPosition = p;}
		virtual ofPoint getOffscreenPosition() {return offscreenPosition;}
		virtual void setOffscreenPosition(ofPoint p) {offscreenPosition = p;}

		virtual ofRectangle getGridRect() {return gridRect;}
		virtual ofRectangle getTileRect() {return tileRect;}

		virtual tile* getWhenFocused() {return 0;}

    protected:

		void setupTileRect();

		int state;
		int id;
		bool clickable;

		ofPoint defaultPosition;
		ofPoint offscreenPosition;

		ofRectangle gridRect;
		ofRectangle tileRect;

		list<animation*> animations;

	private:

		virtual void set(int id, ofRectangle gridRect, bool clickable);
};