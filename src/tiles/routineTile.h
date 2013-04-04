#pragma once

#include "ofMain.h"
#include "tile.h"
#include "pointAnimation.h"

class routineTile : public tile {

    public:

		routineTile();
		routineTile(int id);
		routineTile(int id, ofRectangle gridRect);
		routineTile(int id, ofRectangle gridRect, bool clickable);
		~routineTile();

        virtual bool mousePressed(int x, int y, int button);

		virtual void checkStateTransition();

		virtual void setState(int newState);

    protected:
		
		bool clickable;

	private:

		void set(int id, ofRectangle gridRect, bool clickable);
};