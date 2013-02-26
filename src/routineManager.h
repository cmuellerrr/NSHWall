#pragma once

#include "ofMain.h"
#include "routine.h"

#define IDLE_THRESHOLD 1

class routineManager {

    public:

        routineManager();
		~routineManager();

        void update();
        void draw();

		void keyPressed(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

		void addRoutine(routine r);
		void removeRoutine(routine* r);

		void cycleRoutine();
		void setNextRoutine(routine* r);
   
    private:
		int getRoutineIndex(routine* r);
		routine* getRoutineAt(int index);

		list<routine> routines;
	    routine* activeRoutine;
		routine* nextRoutine;

		long lastHit;
};