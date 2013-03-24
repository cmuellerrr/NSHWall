#ifndef VIEW_H
#define VIEW_H

#pragma once

#include "ofMain.h"
#include "ofxAnimatableOfPoint.h"
#include "featureTile.h"
#include "ofxLibRocket.h"


//The margin surrounding an individual tile
#define MARGIN_TILE 5

class tile : ofxLibRocketCustomElement {

    public:

        tile(float column, float row, float columnSpan, float rowSpan, ofxLibRocket &libRocket, bool click = true);
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
        featureTile feature;
    
        Rocket::Core::String tileId;
    
    private:
        Rocket::Core::Context * context;
};

#endif VIEW_H