#pragma once

#include "ofMain.h"
#include "tileGroup.h"

//Represent the possible states of a routine.
enum{ENTER, ACTIVE, EXIT, HIDDEN, FADE_IN, FADE_OUT};

class routine {

    public:

		routine(int id, string name);
		~routine();

		void update();
		void draw();

        bool mouseMoved(int x, int y, int screen);
        bool mouseDragged(int x, int y, int button, int screen);
        bool mousePressed(int x, int y, int button, int screen);
        bool mouseReleased(int x, int y, int button, int screen);

		int getId() {return id;}
		int getState() {return state;}
		void setState(int newState);

		void addGroup(tileGroup g);
		void removeGroup(tileGroup* g);

	protected:
		int state;
		
	private:
		bool isAnimating();
		void setupEntrance();
		void setupExit();

		int getGroupIndex(tileGroup* g);
		tileGroup* getGroupAt(int index);

		int id;
		string name;
		unsigned int start;
		unsigned int end;
		list<tileGroup> groups;
};