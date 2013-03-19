#ifndef VIEW_H
#define VIEW_H

#pragma once

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxLibRocketCustomElement.h"
#include "featureTile.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile : ofxLibRocketCustomElement {

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

		void setupEntrance(int edge);
		void setupExit(int edge);

		featureTile* getFeature() {return &feature;}

    protected:
		ofPoint getOffscreenPosition(int edge);

		bool clickable;
		ofPoint finalPosition;

		ofxAnimatableOfPoint position;

		ofRectangle gridRect;
		ofRectangle tileRect;
<<<<<<< HEAD
};

#endif VIEW_H
=======

		featureTile feature;
};
>>>>>>> master
