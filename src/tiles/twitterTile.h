#pragma once

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "routineTile.h"
#include "pointAnimation.h"

#define DISPLAY_THRESHOLD 5000

struct tweet {
	string date;
	int userId;
	string userName;
	string profileImageUrl;
	string text;
};

class twitterTile : public routineTile {

    public:

		twitterTile();
		twitterTile(int id);
		twitterTile(string tag);
		twitterTile(int id, string tag);
		twitterTile(int id, string tag, ofRectangle gridRect);
		~twitterTile();

		void draw();
		void update();

		void checkStateTransition();

		void setState(int newState);

		void setTag(string newTag);

    protected:

		string tag;
		list<tweet> tweets;
		tweet* activeTweet;

		unsigned long lastSwitch;

	private:

		void set(int id, string tag, ofRectangle gridRect);
		
		void setupTweets();
		tweet parseTweet(ofxJSONElement json);

		int getTweetIndex(tweet* t);
		tweet* getTweetAt(int index);
};