#pragma once

#include "ofMain.h"
#include "dimensionAnimation.h"

//The margin surrounding a feature story
#define MARGIN_FEATURE 5

class expandedTile {

    public:

		expandedTile();
		expandedTile(int id, string title);
		~expandedTile();

        void update();
		void draw();

        bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

		bool isAnimating();

		void setState(int newState);
		int getState() {return state;}
		void setContent(string newContent);

		void addImage(ofImage img);

	protected:
		
		int state;
		int id;

	private:
		string title;
		string content;

		ofPoint finalSize;

		ofRectangle tileRect;

		list<ofImage> images;
		list<animation*> animations;
};