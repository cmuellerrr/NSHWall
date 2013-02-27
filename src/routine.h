#pragma once

#include "ofMain.h"
#include "tileGroup.h"

enum{ENTER, ACTIVE, EXIT, DONE};

class routine {

    public:

		routine();
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
				case DONE:
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
				case DONE:
					break;
			}	
		}

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

		void setMode(int newMode);
		int getMode() {return mode;}
  
		void addGroup(tileGroup g);
    
		void setupEntrance();
		void setupExit();

	protected:
		int mode;
		
	private:
		list<tileGroup> groups;
};