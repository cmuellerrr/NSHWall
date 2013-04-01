#pragma once

#include "ofMain.h"
#include "tile.h"
#include "expandedTile.h"
#include "pointAnimation.h"

//The margin surrounding an individual tile
#define MARGIN_TILE 5

class gridTile : public tile {

    public:

		gridTile();
		gridTile(int id, string title);
		gridTile(int id, string title, string content);
		gridTile(int id, string title, ofRectangle gridRect);
		gridTile(int id, string title, ofRectangle gridRect, bool clickable);
		gridTile(int id, string title, string content, ofRectangle gridRect);
		gridTile(int id, string title, string content, ofRectangle gridRect, bool clickable);
		~gridTile();

		void draw();

        bool mousePressed(int x, int y, int button);

		void checkStateTransition();

		void setState(int newState);
		
		tile* getWhenFocused() {return &expanded;}

		void setContent(string content);

		void setFeaturedImage(string url);
		void setFeaturedImage(ofImage img);

		void addImage(string url);
		void addImage(ofImage img);

    protected:
		
		string title;
		ofImage featuredImg;			
		
		expandedTile expanded;

	private:

		void set(int id, string title, string content, ofRectangle gridRect, bool clickable);
};