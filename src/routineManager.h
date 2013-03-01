#pragma once

#include "ofMain.h"
#include "routine.h"

//How long, in milliseconds, a routine may stay idle before
//transitioning to a new routine.
#define IDLE_THRESHOLD 15000

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
		void setIncomingRoutine(routine* r);
   
    private:
		int getRoutineIndex(routine* r);
		routine* getRoutineAt(int index);
		void resetHitTimer();


		list<routine> routines;
	    routine* activeRoutine;
		routine* incomingRoutine;

		unsigned long lastHit;
};