/*
 * A class that handles the creation of routines, tile groups, and tiles.
 * This should be used to ease the burden on other classes when getting 
 * the info from the CMS.
 *
 * This is just a namespace so it can be used essentially as a static class.
 */

#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "routine.h"
#include "wall.h"

//NOTE: Order of function declaration matters here!!!
namespace routineFactory {

    tileGroup getTestTiles1(int index, ofRectangle bounds) {
		tileGroup testGroup = tileGroup(index, bounds);
			
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 1, 2, 2)));
		
		//tile t2 = tile(ofRandom(256), "Test", ofRectangle(2, 1, 2, 1));
		//t2.setFeaturedImage("http://robowall.hcii.cs.cmu.edu/wp-content/uploads/2013/03/1.jpg");
		//t2.setFeaturedImage("layouts/chris.jpg");
		//testGroup.addTile(t2);

		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(2, 1, 2, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(2, 2, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(3, 2, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 3, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1, 3, 3, 2)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 4, 1, 1)));

		return testGroup;
	};

	tileGroup getTestTiles2(int index, ofRectangle bounds) {
		tileGroup testGroup = tileGroup(index, bounds);
			
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 0, 4, .5)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 1, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1, 1, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(2, 1, 2, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 2, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1, 2, 2, 2), false));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(3, 2, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 3, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(3, 3, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 4, 2, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(2, 4, 2, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 5.5, 4, .5), false));

		return testGroup;
	};

	tileGroup getTestTiles3(int index, ofRectangle bounds) {
		tileGroup testGroup = tileGroup(index, bounds);
			
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 1, 1.5, 2)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1.5, 1, 2.5, 2)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 3, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1, 3, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(2, 3, 2, 2)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(0, 4, 1, 1)));
		testGroup.addTile(tile(ofRandom(256), "Test", ofRectangle(1, 4, 1, 1)));

		return testGroup;
	};
		
	/*
	 * Create a test routine based on the number of sceens (up to 3)
	 */
	routine getTestRoutine(int id, string name) {
		routine testRoutine = routine(id, name);
		
		if (SCREENS >= 1) {
			testRoutine.addGroup(getTestTiles1(0, ofRectangle(MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
		
			if (SCREENS >= 2) {
				testRoutine.addGroup(getTestTiles2(1, ofRectangle(wall::SCREEN_W + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
			
				if (SCREENS >= 3) {
					testRoutine.addGroup(getTestTiles3(2, ofRectangle((wall::SCREEN_W * 2) + MARGIN_GROUP, MARGIN_GROUP, wall::GROUP_W, wall::GROUP_H)));
				}
			}
		}

		return testRoutine;
	};
	
	/*
	 * Organize the given routine to include the given tiles.
	 * The routine will sort the tiles into tileGroups.
	 * Tiles need to be layed out in a grid according to their
	 * preferred size vs the amount of space available.
	 */
	void organizeRoutine(routine* r, list<tile>* t) {
		//TODO Organize the tiles into groups and lay them out
	};

	/*
	 * Create a new tile object by parsing the given json
	 * element.
	 */
	tile parseTile(ofxJSONElement json) {
		tile newTile = tile(json["id"].asInt(), json["title"].asString(), json["content"].asString());
		
		for (int i = 0; i < json["media"].size(); i++) {
			if (i == 0) newTile.setFeaturedImage(json["media"][i].asString());
			else newTile.addImage(json["media"][i].asString());
		}
		
		return newTile;
	};

	/*
	 * Creat a new routine object by parsing the given 
	 * json element.
	 */
	routine parseRoutine(ofxJSONElement json) {
		routine newRoutine = routine(json["id"].asInt(), json["name"].asString());
		//TODO Get the other stuff like start and stop dates
		return newRoutine;
	};

	/*
	 * Create a list of routine objects based off of the 
	 * given json element.
	 */
	list<routine> parseRoutines(ofxJSONElement json) {
		ofxJSONElement jsonRoutines = json["routines"];
		ofxJSONElement jsonArticles = json["articles"];
		list<routine> routines;

		//Create all the routine objects
		for (int i = 0; i < jsonRoutines.size(); i++) {
			routine newRoutine = parseRoutine(jsonRoutines[i]);

			int routineId = newRoutine.getId();
			list<tile> routineTiles;

			//Get a list of all the tiles associated with a routine
			for (int j = 0; j < jsonArticles.size(); j++) {
				ofxJSONElement relatedRoutines = jsonArticles[j]["routines"];

				//Check to see that the article is associated
				for (int k = 0; k < relatedRoutines.size(); k++) {
					if (routineId == relatedRoutines[k].asInt()) {
						routineTiles.push_back(parseTile(jsonArticles[j]));
					}
				}
			}

			organizeRoutine(&newRoutine, &routineTiles);
			routines.push_back(newRoutine);
		}

		return routines;
	};
};