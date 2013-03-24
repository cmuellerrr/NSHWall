#pragma once

#include "ofMain.h"
#include "tileGroup.h"

//Represent the possible states of a routine.
enum{ENTER, ACTIVE, EXIT, HIDDEN};

class routine {

    public:

		routine(int id);
		~routine();

        void update() {
			switch (mode) {
				case ENTER:
					updateEnter();
					break;
				case ACTIVE:
					updateActive();
					break;
				case EXIT:
					updateExit();
					break;
				case HIDDEN:
					break;
			}	
		}

        void draw() {
			switch (mode) {
				case ENTER:
					drawEnter();
					break;
				case ACTIVE:
					drawActive();
					break;
				case EXIT:
					drawExit();
					break;
				case HIDDEN:
					break;
			}	
		}

		void updateEnter();
		void updateActive();
		void updateExit();

		void drawEnter();
		void drawActive();
		void drawExit();

        bool mouseMoved(int x, int y, int screen);
        bool mouseDragged(int x, int y, int button, int screen);
        bool mousePressed(int x, int y, int button, int screen);
        bool mouseReleased(int x, int y, int button, int screen);

		int getId() {return id;}
		void setMode(int newMode);
		int getMode() {return mode;}
  
		void addGroup(tileGroup g);
		void removeGroup(tileGroup* g);

	protected:
		int mode;
		
	private:
		void setupEntrance();
		void setupExit();

		int getGroupIndex(tileGroup* g);
		tileGroup* getGroupAt(int index);

		int id;
		list<tileGroup> groups;
};