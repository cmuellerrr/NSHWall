#pragma once

#include "ofMain.h"

#include "ofxFensterManager.h"
#include "ofxFensterCanvas.h"

#include "routineManager.h"

#define SCREENS 3
#define ROWS 6
#define COLUMNS 4

enum{EDGE_LEFT, EDGE_TOP, EDGE_BOTTOM, EDGE_RIGHT};

class wall : public ofxFensterListener{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		static float SCREEN_W;
		static float SCREEN_H;
		static float GROUP_W;
		static float GROUP_H;
		static float TILE_W;
		static float TILE_H;

	private:
		ofxFensterCanvas canvas;

		routineManager manager;
};
