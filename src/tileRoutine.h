#pragma once

#include "ofMain.h"
#include "routine.h"
#include "tileGroup.h"

class tileRoutine : public routine {

    public:

        tileRoutine();
		~tileRoutine();

		void updateEnter();
		void updateActive();
		void updateExit();

		void drawEnter();
		void drawActive();
		void drawExit();

        bool mouseMoved(int x, int y);
        bool mouseDragged(int x, int y, int button);
        bool mousePressed(int x, int y, int button);
        bool mouseReleased(int x, int y, int button);

    private:
	    list<tileGroup> groups;
};