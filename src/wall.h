#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxFensterCanvas.h"
#include "routineManager.h"
#include "ofxLibRocket.h"

//General variable for the wall
#define SCREENS 3
#define ROWS 6
#define COLUMNS 4

//Representing edges of the overall wall.
enum{EDGE_LEFT, EDGE_TOP, EDGE_BOTTOM, EDGE_RIGHT};

class wall : public ofxFensterListener {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key, ofxFenster* f);
		void keyReleased(int key, ofxFenster* f);
		void mouseMoved(int x, int y, ofxFenster* f);
		void mouseDragged(int x, int y, int button, ofxFenster* f);
		void mousePressed(int x, int y, int button, ofxFenster* f);
		void mouseReleased(int x, int y, int button, ofxFenster* f);
		void windowResized(int w, int h, ofxFenster* f);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        static ofxLibRocket getOfxLibRocket(wall &instance);

		static float SCREEN_W;
		static float SCREEN_H;
		static float GROUP_W;
		static float GROUP_H;
		static float TILE_W;
		static float TILE_H;
        static float ASPECT_RATIO;
    
        ofxLibRocket libRocket;
        ofxLibRocketDocument* doc;

	private:
		int getWindowIndex(ofxFenster* f);

		ofxFensterCanvas canvas;

		routineManager manager;
};
