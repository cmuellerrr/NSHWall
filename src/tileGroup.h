#pragma once

#include "ofMain.h"
#include "tile.h"

//The margin surrounding a tile group.
#define MARGIN_GROUP 10

//Representing the relative position of a tile group compared 
//to the entire wall
enum{FARLEFT, MIDDLE, FARRIGHT};

class tileGroup {

    public:

        tileGroup();
		tileGroup(ofRectangle bounds);
		~tileGroup();

		void update();
		void draw();
        
		bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		void addTile(tile t);

		bool isAnimating();

		void setupEntrance();
		void setupExit();

    private:
		int randomScreenEdge();
		
		int relativePosition;

		ofRectangle boundingBox;
		ofColor tileColor;

	    list<tile> tiles;
		tile* focus;
};