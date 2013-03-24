/*
 * A class that handles the creation of routines, tile groups, and tiles.
 * This should be used to ease the burden on other classes when getting 
 * the info from the CMS.
 */

#pragma once

#include "ofMain.h"
#include "routine.h"
#include "wall.h"
#include "ofxLibRocket.h"

class routineFactory {

    public:

		/*
		 * Create a test routine based on the number of sceens (up to 3)
		 */
		static routine getTestRoutine(int id, ofxLibRocket &libRocketReference) {
			routine testRoutine = routine(id);

			if (SCREENS >= 1) {
					testRoutine.addGroup(getTestTiles1(ofRectangle(MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H), 0, libRocketReference));
			
				if (SCREENS >= 2) {
					testRoutine.addGroup(getTestTiles2(ofRectangle(wall::SCREEN_W + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H), 1, libRocketReference));
				
					if (SCREENS >= 3) {
						testRoutine.addGroup(getTestTiles3(ofRectangle((wall::SCREEN_W * 2) + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H), 2, libRocketReference));
					}
				}
			}

			return testRoutine;
		}

        static tileGroup getTestTiles1(ofRectangle bounds, int index, ofxLibRocket &libRocketReference) {
			tileGroup testGroup = tileGroup(bounds, index);
			
			testGroup.addTile(tile(0, 1, 2, 2, libRocketReference));
			testGroup.addTile(tile(2, 1, 2, 1, libRocketReference));
			testGroup.addTile(tile(2, 2, 1, 1, libRocketReference));
			testGroup.addTile(tile(3, 2, 1, 1, libRocketReference));
			testGroup.addTile(tile(0, 3, 1, 1, libRocketReference));
			testGroup.addTile(tile(1, 3, 3, 2, libRocketReference));
			testGroup.addTile(tile(0, 4, 1, 1, libRocketReference));

			return testGroup;
		}

		static tileGroup getTestTiles2(ofRectangle bounds, int index, ofxLibRocket &libRocketReference) {
			tileGroup testGroup = tileGroup(bounds, index);
			
			testGroup.addTile(tile(0, 0, 4, .5, libRocketReference));
			testGroup.addTile(tile(0, 1, 1, 1, libRocketReference));
			testGroup.addTile(tile(1, 1, 1, 1, libRocketReference));
			testGroup.addTile(tile(2, 1, 2, 1, libRocketReference));
			testGroup.addTile(tile(0, 2, 1, 1, libRocketReference));
			testGroup.addTile(tile(1, 2, 2, 2, libRocketReference, false));
			testGroup.addTile(tile(3, 2, 1, 1, libRocketReference));
			testGroup.addTile(tile(0, 3, 1, 1, libRocketReference));
			testGroup.addTile(tile(3, 3, 1, 1, libRocketReference));
			testGroup.addTile(tile(0, 4, 2, 1, libRocketReference));
			testGroup.addTile(tile(2, 4, 2, 1, libRocketReference));
			testGroup.addTile(tile(0, 5.5, 4, .5, libRocketReference, false));

			return testGroup;
		}

		static tileGroup getTestTiles3(ofRectangle bounds, int index, ofxLibRocket &libRocketReference) {
			tileGroup testGroup = tileGroup(bounds, index);
			
			testGroup.addTile(tile(0, 1, 1.5, 2, libRocketReference));
			testGroup.addTile(tile(1.5, 1, 2.5, 2, libRocketReference));
			testGroup.addTile(tile(0, 3, 1, 1, libRocketReference));
			testGroup.addTile(tile(1, 3, 1, 1, libRocketReference));
			testGroup.addTile(tile(2, 3, 2, 2, libRocketReference));
			testGroup.addTile(tile(0, 4, 1, 1, libRocketReference));
			testGroup.addTile(tile(1, 4, 1, 1, libRocketReference));

			return testGroup;
		}
   
    private:
		
};