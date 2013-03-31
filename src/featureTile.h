#pragma once

#include "ofMain.h"
#include "dimensionAnimation.h"

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

		void setState(int newState);
		int getState() {return state;}

    private:
		void setupEntrance();
		void setupExit();

		int state;

		ofPoint finalSize;

		ofRectangle tileRect;

		list<animation*> animations;
};