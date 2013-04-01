#pragma once

#include "ofMain.h"
#include "tile.h"
#include "dimensionAnimation.h"

//The margin surrounding a feature story
#define MARGIN_FEATURE 5

class expandedTile : public tile {

    public:

		expandedTile();
		expandedTile(int id, string title);
		expandedTile(int id, string title, string content);
		~expandedTile();

		void draw();

        bool mousePressed(int x, int y, int button);

		void checkStateTransition();

		bool isAnimating();

		void setState(int newState);
		void setContent(string newContent);

		void addImage(ofImage img);

	protected:
		
		string title;
		string content;

		ofPoint finalSize;

		list<ofImage> images;

	private:

		void set(int id, string title, string content);
};