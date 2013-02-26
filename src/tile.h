#pragma once

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"

#define MARGIN_TILE 5

class tile {

    public:

        tile();
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

    protected:
		bool clickable;
		ofPoint finalPosition;

		ofxAnimatableOfPoint path;

		ofRectangle gridRect;
		ofRectangle tileRect;
};