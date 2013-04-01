/*
 * A basic web interface to the robowall content management system.  
 *
 * This is just a namespace so it can be used essentially as a static class.
 */

#pragma once

#include "ofxJSONElement.h"

namespace webInterface {

	namespace {
		ofxJSONElement getJSON(string url) {
			ofxJSONElement json;
			bool success = json.open(url);

			if (!success) {
				cout<<"Failed to get response.\n";\
			}
			return json;
		}
	};

    ofxJSONElement getActiveRoutines() {
        cout<<"Getting active routines.\n";
		return getJSON("http://robowall.hcii.cs.cmu.edu/?wpapi=get_posts&type=post&dev=1");
    };

	ofxJSONElement getTweets(string tag) {
		cout<<"Getting tweets: "<<tag<<" \n";
		return getJSON("http://search.twitter.com/search.json?q=%23" + tag);
    };	
};