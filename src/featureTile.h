#pragma once

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"
#include "routine.h"

//The margin surrounding a feature story
#define MARGIN_FEATURE 5

class featureTile {

    public:

		featureTile();
		~featureTile();

        void update();
		void draw();

        bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		bool isAnimating();

		void setupEntrance();
		void setupExit();

		void setMode(int newMode);
		int getMode() {return mode;}

    protected:
		int mode;

		ofPoint finalSize;
		ofxAnimatableOfPoint size;

		ofRectangle tileRect;
};