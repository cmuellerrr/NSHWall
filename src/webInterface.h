/*
 * A basic web interface to the robowall content management system.  
 *
 * This is just a namespace so it can be used essentially as a static class.
 */

#pragma once

#include "ofxJSONElement.h"

namespace webInterface {

    string getActiveRoutines() {
        cout<<"Getting active routines.\n";
        ofxJSONElement json;
		bool success = json.open("http://robowall.hcii.cs.cmu.edu/?wpapi=get_posts&type=post&dev=1");

		if (success) {
			return json.getRawString();
		} else {
			cout<<"Failed to get active routines.\n";
			return "";
		}
    }

}