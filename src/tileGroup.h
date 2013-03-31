#pragma once

#include "ofMain.h"
#include "gridTile.h"
#include "expandedTile.h"

//The margin surrounding a tile group.
#define MARGIN_GROUP 10

class tileGroup {

    public:

        tileGroup();
		tileGroup(int index, ofRectangle bounds);
		~tileGroup();

		void set(int index, ofRectangle bounds);

		void update();
		void draw();
        
		bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		void setupEntrance();
		void setupExit();

		void addTile(gridTile t);
		void removeTile(gridTile* t);

		bool isAnimating();

		int getIndex() {return index;}

    private:
		ofPoint getClosestOffscreenPosition(gridTile t);

		int getTileIndex(gridTile* t);
		gridTile* getTileAt(int index);

		int index;

		ofRectangle boundingBox;

	    list<gridTile> tiles;
		expandedTile* focus;

		ofColor tileColor;
};