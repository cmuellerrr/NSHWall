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

		virtual void draw();

        virtual bool mousePressed(int x, int y, int button);

		virtual void checkStateTransition();

		virtual void setState(int newState);

		virtual void setContent(string newContent) {content = newContent;}

		virtual void addImage(ofImage img);

	protected:
		
		virtual void translateGridDimensions();

		string title;
		string content;

		ofPoint defaultSize;

		list<ofImage> images;

	private:

		void set(int id, string title, string content);
};