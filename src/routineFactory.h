#pragma once

#include "ofMain.h"
#include "routine.h"
#include "wall.h"

class routineFactory {

    public:

		static routine getTestRoutine() {
			routine testRoutine = routine();

			if (SCREENS >= 1) {
					testRoutine.addGroup(getTestTiles1(ofRectangle(MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
			
				if (SCREENS >= 2) {
					testRoutine.addGroup(getTestTiles2(ofRectangle(wall::SCREEN_W + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
				
					if (SCREENS >= 3) {
						testRoutine.addGroup(getTestTiles3(ofRectangle((wall::SCREEN_W * 2) + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
					}
				}
			}

			return testRoutine;
		}

        static tileGroup getTestTiles1(ofRectangle bounds) {
			tileGroup testGroup = tileGroup(bounds);
			
			testGroup.addTile(tile(0, 1, 2, 2));
			testGroup.addTile(tile(2, 1, 2, 1));
			testGroup.addTile(tile(2, 2, 1, 1));
			testGroup.addTile(tile(3, 2, 1, 1));
			testGroup.addTile(tile(0, 3, 1, 1));
			testGroup.addTile(tile(1, 3, 3, 2));
			testGroup.addTile(tile(0, 4, 1, 1));

			return testGroup;
		}

		static tileGroup getTestTiles2(ofRectangle bounds) {
			tileGroup testGroup = tileGroup(bounds);
			
			testGroup.addTile(tile(0, 0, 4, .5));
			testGroup.addTile(tile(0, 1, 1, 1));
			testGroup.addTile(tile(1, 1, 1, 1));
			testGroup.addTile(tile(2, 1, 2, 1));
			testGroup.addTile(tile(0, 2, 1, 1));
			testGroup.addTile(tile(1, 2, 2, 2, false));
			testGroup.addTile(tile(3, 2, 1, 1));
			testGroup.addTile(tile(0, 3, 1, 1));
			testGroup.addTile(tile(3, 3, 1, 1));
			testGroup.addTile(tile(0, 4, 2, 1));
			testGroup.addTile(tile(2, 4, 2, 1));
			testGroup.addTile(tile(0, 5.5, 4, .5, false));

			return testGroup;
		}

		static tileGroup getTestTiles3(ofRectangle bounds) {
			tileGroup testGroup = tileGroup(bounds);
			
			testGroup.addTile(tile(0, 1, 1.5, 2));
			testGroup.addTile(tile(1.5, 1, 2.5, 2));
			testGroup.addTile(tile(0, 3, 1, 1));
			testGroup.addTile(tile(1, 3, 1, 1));
			testGroup.addTile(tile(2, 3, 2, 2));
			testGroup.addTile(tile(0, 4, 1, 1));
			testGroup.addTile(tile(1, 4, 1, 1));

			return testGroup;
		}
   
    private:
		
};